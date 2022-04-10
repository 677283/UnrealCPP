#include "CBTTaskNode_SpawnClone.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_SpawnClone::UCBTTaskNode_SpawnClone()
{
	NodeName = "Subjugate";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_SpawnClone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI_Boss* character = Cast<ACEnemy_AI_Boss>(controller->GetPawn());
	character->Dash();

	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_SpawnClone::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI_Boss* character = Cast<ACEnemy_AI_Boss>(controller->GetPawn());

	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	ACharacter* target = behavior->GetTargetCharacter();

	CheckNull(target);
	CheckNull(character);

	if (!character->IsPattern())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt("Pattern", 0);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("WaitTime", 1.0f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}