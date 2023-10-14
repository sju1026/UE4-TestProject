// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RandomMove.h"
#include "MyTestGame.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "MyTestGameAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "blackboard_keys.h"

UMyBTTask_RandomMove::UMyBTTask_RandomMove(FObjectInitializer const& object_initializer) {
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UMyBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const cont = Cast<AMyTestGameAIController>(OwnerComp.GetAIOwner());
	auto const npc = cont->GetPawn();

	FVector const origin = npc->GetActorLocation();
	FNavLocation loc;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());

	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
	}

	/*UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

	AMyTestGameAIController* MyController = Cast<AMyTestGameAIController>(OwnerComp.GetAIOwner());

	if (NavSys && MyController && MyController->GetPawn()) {
		const float SearchRadius = 200.0f;
		FNavLocation RandomPt;

		const bool bFound = NavSys->GetRandomPointInNavigableRadius(MyController->GetPawn()->GetActorLocation(), search_radius, RandomPt);

		if (bFound) {
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(GetSelectedBlackboardKey(), RandomPt.Location);

			return EBTNodeResult::Succeeded;
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Failed;*/

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

