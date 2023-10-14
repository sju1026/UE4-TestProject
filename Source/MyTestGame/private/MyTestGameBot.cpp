// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameBot.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectile.h"
#include "blackboard_keys.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
// #include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"

AMyTestGameBot::AMyTestGameBot() {

	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(20.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "WeaponPoint");

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyTestGameBot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AActor::StaticClass()) && PlayAnimMontage(montage) > 0.2f && !me)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
	}
}

int AMyTestGameBot::melee_attack_Implementation()
{
	
	if (montage) {
		if (MyBotName == "Melee" || MyBotName == "Boss") {
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Attack");
			PlayAnimMontage(montage);
		}
		else if (MyBotName == "Range" && MyBullet) {
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(80.0f, 35.0f, 10.0f));
			UWorld* const World = GetWorld();
			if (World != NULL) {
				World->SpawnActor<AMyProjectile>(MyBullet, SpawnLocation, SpawnRotation);
			}
		}
	}

	return 0;
}


UAnimMontage* AMyTestGameBot::get_montage() const
{
	return montage;
}
