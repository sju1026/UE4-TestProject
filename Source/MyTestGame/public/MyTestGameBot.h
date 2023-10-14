// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "MyTestGameBot.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AMyTestGameBot : public ABasicCharacter, public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AMyTestGameBot();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		class USphereComponent* WeaponCollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyBotName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		TSubclassOf<class AMyProjectile> MyBullet;

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;

	class AMyTestGameBot* me;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;
};