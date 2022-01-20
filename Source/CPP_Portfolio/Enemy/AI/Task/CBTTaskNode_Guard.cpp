#include "CBTTaskNode_Guard.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_Guard::UCBTTaskNode_Guard()
{
	NodeName = "Guard";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Guard::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("GuardDirection", GetRandomGuardDirection());

	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_Guard::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* character = Cast<ACEnemy_AI>(controller->GetPawn());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);


	if (behavior->GetTargetCharacter() == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		return;
	}
	else if (character->CanAttack())
	{
		CLog::Log("WTF");
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		return;
	}

	ACharacter* target = behavior->GetTargetCharacter();

	float distance = character->GetDistanceTo(target);

	float rnd = FMath::FRand();

	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;

	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, DeltaSeconds, 10));


	float dir = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("GuardDirection");
	if (distance > 400)
	{
		character->MoveForward(1);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bInGuard", true);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("GuardDirection", GetRandomGuardDirection());
	}
	else if (distance < 200)
	{
		character->MoveForward(-1);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("bInGuard", false);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("GuardDirection", GetRandomGuardDirection());
	}
	else if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("bInGuard"))
	{
		character->MoveForward(1);
		character->MoveRight(dir);
	}
	else
		character->MoveRight(dir);
}

float UCBTTaskNode_Guard::GetRandomGuardDirection()
{
	float dir = FMath::FRand();

	dir < 0.5f ? dir = -1 : dir = 1;

	return dir;
}
