#include "CBTTaskNode_BossAttack.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"

UCBTTaskNode_BossAttack::UCBTTaskNode_BossAttack()
{
	NodeName = "Approach";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	CLog::Log("BossAttackTask : InAttack");
	
	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI_Boss* character = Cast<ACEnemy_AI_Boss>(controller->GetPawn());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACharacter* target = behavior->GetTargetCharacter();

	CheckNull(target);

	if (target->GetDistanceTo(character) < 250)
	{
		character->Boss_Attack();
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}


