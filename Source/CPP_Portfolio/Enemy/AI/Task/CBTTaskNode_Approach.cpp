#include "CBTTaskNode_Approach.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI.h"

UCBTTaskNode_Approach::UCBTTaskNode_Approach()
{
	NodeName = "Approach";
}

EBTNodeResult::Type UCBTTaskNode_Approach::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_Approach::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());
	
	
	//FVector targetDir = controller->GetTarget()->GetActorLocation() - character->GetActorLocation();
	//targetDir.Z = 0;
	ACharacter* target = controller->GetTarget();
	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(target->GetActorLocation(), character->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;

	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, DeltaSeconds, 0.5f));
	character->MoveForward(1);

	if ((target->GetActorLocation() - character->GetActorLocation()).Size() < 50)
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
}