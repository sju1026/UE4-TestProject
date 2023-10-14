// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AMyTestGameCharacter::AMyTestGameCharacter() {
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FolloCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FolloCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FolloCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	setup_stimulus();
}

void AMyTestGameCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

void AMyTestGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTestGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTestGameCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyTestGameCharacter::InputJump);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABasicCharacter::Attack_Melee);
	PlayerInputComponent->BindAction("Change", IE_Pressed, this, &ABasicCharacter::OnChangeWeapon);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyTestGameCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyTestGameCharacter::SprintEnd);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyTestGameCharacter::Dashing);

	PlayerInputComponent->BindAxis("Turn", this, &AMyTestGameCharacter::InputTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyTestGameCharacter::InputLookUp);
}

void AMyTestGameCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !isDuringAttack) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMyTestGameCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !isDuringAttack) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void AMyTestGameCharacter::InputJump()
{
	Jump();
}

void AMyTestGameCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
}

void AMyTestGameCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMyTestGameCharacter::Dashing()
{
	const FVector forwardDir = this->GetActorRotation().Vector();
	LaunchCharacter(forwardDir * dashDistance, true, true);
	if (dashMontage)
	{
		PlayAnimMontage(dashMontage, 1, FName("Dash"));
	}
}

void AMyTestGameCharacter::InputTurn(float value)
{
	this->AddControllerYawInput(value);
}

void AMyTestGameCharacter::InputLookUp(float value)
{
	this->AddControllerPitchInput(value);
}

void AMyTestGameCharacter::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}
