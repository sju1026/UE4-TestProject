// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Engine.h"
#include "MyTestGameBot.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "MyTestGameCharacter.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bSpawn = false;
	enemyNum = 0;
	bossCount = 0;
	bossMaxCount = 1;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnPointCom"));
	CollisionSphere->InitSphereRadius(1000.0f);
	RootComponent = CollisionSphere;

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ASpawnPoint::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugSphere(GetWorld(), GetActorLocation(), 1000.0f, 50, FColor::Green, true, -1, 0, 2);
	maxEnemyNum = spawnPointValue * 4;
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawn) {

		currentTime = currentTime + 1 * DeltaTime;
		if (currentTime >= 2.0f) {
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = this->GetInstigator();

			UWorld* WRLD = GetWorld();

			FVector location = GetActorLocation();
			FRotator rotation = GetActorRotation();
			if (enemyNum <= maxEnemyNum)
			{
				for (int i = 0; i < myBot.Num() - 1; ++i)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Enemy Count : %d"), enemyNum));
					AMyTestGameBot* myNewBot = WRLD->SpawnActor<AMyTestGameBot>(myBot[i], location, rotation);
					enemyNum++;
				}
			}
			else if (bossCount < bossMaxCount)
			{
				AMyTestGameBot* myNewBot = WRLD->SpawnActor<AMyTestGameBot>(myBot[2], location, rotation);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Boss is Comming");
				bossCount++;
			}
				
			currentTime = 0.0f;
		}	
	}
}

void ASpawnPoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyTestGameCharacter::StaticClass())) {
		if (!bSpawn) {
			bSpawn = true;
		}
	}
}

void ASpawnPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMyTestGameCharacter::StaticClass())) {
		if (bSpawn) {
			bSpawn = false;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Player Out!");
		}
	}
}

