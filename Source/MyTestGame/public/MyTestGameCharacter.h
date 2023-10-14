// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Engine/DataTable.h"
#include "MyTestGameCharacter.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterInfo :public FTableRowBase {
	GENERATED_BODY()
public:
	FCharacterInfo() {
		CharacterName = FText::FromString("Name");
		CharacterLevel = 1;
		Description = FText::FromString("My Character is ....");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CharacterThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
};

UCLASS()
class MYTESTGAME_API AMyTestGameCharacter : public ABasicCharacter
{
	GENERATED_BODY()
	
public:
	AMyTestGameCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FolloCamera;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* dashMontage;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);

	void MoveRight(float value);

	void InputJump();

	float sprintSpeed = 900.0f;

	void SprintStart();
	void SprintEnd();

	UPROPERTY(EditAnywhere, Category = MyState)
		float dashDistance = 6000;

	void Dashing();

	void InputTurn(float value);

	void InputLookUp(float value);

private:
	class UAIPerceptionStimuliSourceComponent* stimulus;
	void setup_stimulus();

public:
	//PlayerItem Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> MyItemArray_ch;
};
