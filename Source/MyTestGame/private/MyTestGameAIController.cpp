// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestGameAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyTestGameCharacter.h"
#include "MyTestGameBot.h"
#include "Engine.h"


AMyTestGameAIController::AMyTestGameAIController(FObjectInitializer const& object_initializer) {
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/_My/AI/MyTestGameBot_BT.MyTestGameBot_BT'"));
	if (obj.Succeeded()) {
		btree = obj.Object;
	}


	behavior_tree_Comp = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	setup_perception_system();
}

void AMyTestGameAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(btree);
	behavior_tree_Comp->StartTree(*btree);

	//if (GetPerceptionComponent() != nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("All Systems Set!"));
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("No Component!"));
	//}
}

void AMyTestGameAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	if (blackboard) {
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}

	/*AMyTestGameBot* Bot = Cast<AMyTestGameBot>(pawn);
	if (Bot && Bot->BotBehavior) {
		if (Bot->BotBehavior->BlackboardAsset) {
			blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}
		behavior_tree_Comp->StartTree(*(Bot->BotBehavior));
	}*/
}

void AMyTestGameAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//AMyTestGameCharacter* Chracter = Cast<AMyTestGameCharacter>(GetPawn());

	//if (DistanceToPlayer > AISightRadius) {
	//	bIsPlayerDetected = false;
	//}

	//if (bIsPlayerDetected == true) {
	//	AMyTestGameCharacter* Player = Cast<AMyTestGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//	MoveToActor(Player, 5.0f);
	//}
}

FRotator AMyTestGameAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr) {
		return FRotator(0.f, 0.f, 0.f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

//void AMyTestGameAIController::OnPawnDetected(const TArray<AActor*> &DetectedPawns)
//{
//	/*if (DetectedPawns.Num() > 0) {
//		UE_LOG(LogTemp, Warning, TEXT("Player Enter!"));
//
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("Player Exit!"));
//	}*/
//	for (size_t i = 0; i < DetectedPawns.Num(); i++) {
//		DistanceToPlayer = GetPawn()->GetDistanceTo(DetectedPawns[i]);
//
//		UE_LOG(LogTemp, Warning, TEXT("Distance : %f"), DistanceToPlayer);
//	}
//
//	bIsPlayerDetected = true;
//}

void AMyTestGameAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const ch = Cast<AMyTestGameCharacter>(actor)) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!");
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent* AMyTestGameAIController::get_blackboard() const
{
	return blackboard;
}

void AMyTestGameAIController::setup_perception_system()
{

	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sight_config->SightRadius = 500.0;
	sight_config->LoseSightRadius = sight_config->SightRadius + 50.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 520.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMyTestGameAIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}
