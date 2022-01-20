#include "CBTTaskNode_Attack.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());
	
	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACharacter* target = behavior->GetTargetCharacter();

	CheckNull(target);

	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;

	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, DeltaSeconds, 10));

	float distance = character->GetDistanceTo(target);

	CLog::Log(distance);
	CLog::Log(character->GetAttackRange());

	if (distance > character->GetAttackRange())
		character->MoveForward(1);
	else
		character->Attack();

	if (character->CanAttack() == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);

}
