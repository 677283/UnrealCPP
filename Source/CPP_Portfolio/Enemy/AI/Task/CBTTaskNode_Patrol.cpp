#include "Enemy/AI/Task/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());

	DestPos = UNavigationSystemV1::GetRandomPointInNavigableRadius(character->GetWorld(), character->GetActorLocation(), 300.0f);
	
	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());

	FVector pos1 = character->GetActorLocation();
	FVector pos2 = DestPos;
	pos1.Z = 0;
	pos2.Z = 0;


	character->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(pos1, pos2));
	character->MoveForward(1);

	if (FVector::Dist2D(character->GetActorLocation(), DestPos) <= 50.0f)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}