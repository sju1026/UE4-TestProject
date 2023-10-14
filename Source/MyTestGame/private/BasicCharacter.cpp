// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "MyTestWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include <UObject/ConstructorHelpers.h>
#include <Blueprint/UserWidget.h>
#include <HPBar.h>
#include <Controller_InGame.h>

// Sets default values
ABasicCharacter::ABasicCharacter()
	:myHealth(myMaxHealth), widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDeath = false;
	isDuringAttack = false;
	ComboAttack_Num = 0;
	myHealth = 0.f;
	myMaxHealth = 100.0f;

	if (widget_Component)
	{
		widget_Component->SetupAttachment(RootComponent);
		widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("WidgetBlueprint'/Game/_My/Blueprints/UI/UBP_HpBar.UBP_HpBar_C'"));

		if (widget_class.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			widget_Component->SetWidgetClass(widget_class.Class);

		}
	}

}

////////////////////////////////////////////////////////////////////////
// Weapon

USkeletalMeshComponent* ABasicCharacter::GetSpesificPawnMesh() const
{
	return GetMesh();
}

FName ABasicCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABasicCharacter::AddWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyTestWeapon* NewWeapon, AMyTestWeapon* LastWeapon)
{
	AMyTestWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon) {
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon) {
		LocalLastWeapon->OnUnEqip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void ABasicCharacter::EquipWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABasicCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	/*if (DefaultInventoryClasses[0])
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AMyTestWeapon* NewWeapon = WRLD->SpawnActor<AMyTestWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		AddWeapon(NewWeapon);
	}*/

	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultInventoryClasses[i]) {
			FActorSpawnParameters SpawnInfo;

			UWorld* WRLD = GetWorld();
			AMyTestWeapon* NewWeapon = WRLD->SpawnActor<AMyTestWeapon>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}

}

void ABasicCharacter::OnChangeWeapon()
{
	const int32 CurrentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);

	AMyTestWeapon* NextWeapon = Inventory[(CurrentWeaponIndex + 1) % Inventory.Num()];

	EquipWeapon(NextWeapon);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "change!");
}

//----------------------------------------------------------------------

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	myHealth = myMaxHealth;
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto const uw = Cast<UHPBar>(widget_Component->GetUserWidgetObject());
	float myHPnum = (myHealth / myMaxHealth * 100) * 0.01f;

	if (uw)
	{
		uw->set_bar_value_percent(myHPnum);
	}
}

// =========================================Damage, Die, Hit=========================================

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{


	if (myHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		myHealth -= myGetDamage;
	}


	if (myHealth <= 0)
	{
		if (MyCharacterName == "Player")
		{
			AController_InGame* con = Cast<AController_InGame>(APawn::GetController());
			con->ShowDieUI();
			PlayAnimMontage(Death_AnimMontage, 1.0f);
			Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			PlayAnimMontage(Death_AnimMontage, 1.0f);
			Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
		}

		/*PlayAnimMontage(Death_AnimMontage, 1.0f);
		// Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);

		AController_InGame* con = Cast<AController_InGame>(GetOwner());
		con->ShowDieUI();*/
	}
	else
	{
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), myHealth));
	}


	return myGetDamage;
}

void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage, 1.0f, FName("GetHit"));
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}

}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	isDeath = true;

	myHealth = FMath::Min(0.f, myHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller) {
		Controller->Destroy();
	}

	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasicCharacter::OnDieAnimationEnd, DeathAnimDuration, false);

}

void ABasicCharacter::OnDieAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);

	// UGameplayStatics::OpenLevel(GetWorld(), "/Game/_My/Maps/MainMap");
	// AController_InGame* con = Cast<AController_InGame>(GetOwner());
	// con->ShowDieUI();
}

// ==================================================================================================================================

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicCharacter::Attack_Melee()
{
	if (!isDuringAttack)
	{
		if (ComboAttack_Num < 3)
		{
			int tmp_Num = rand() % 3 + 1;
			FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName(*PlaySection));
			ComboAttack_Num++;

			isDuringAttack = true;

		}
		else
		{
			PlayAnimMontage(Attack_AnimMontage, 1.f, FName("Attack_03"));
			ComboAttack_Num = 0;

			isDuringAttack = true;
		}
	}
}

void ABasicCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
}

float ABasicCharacter::get_Health() const
{
	return myHealth;
}

float ABasicCharacter::get_maxHealth() const
{
	return myMaxHealth;
}

void ABasicCharacter::set_health(float const new_health)
{
	myHealth = new_health;
}
