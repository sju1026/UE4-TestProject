// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MYTESTGAME_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

	UPROPERTY(EditDefaultsOnly, Category = State)
		float myInitialSpeed;

	UPROPERTY(EditDefaultsOnly, Category = State)
		float myMaxSpeed;

	UPROPERTY(EditDefaultsOnly, Category = State)
		FName ProjectileName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(AActor* OhterActor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit);

	FORCEINLINE class USphereComponent* GetProjectileCollision() const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	class ABasicCharacter* MyPawn;
};
