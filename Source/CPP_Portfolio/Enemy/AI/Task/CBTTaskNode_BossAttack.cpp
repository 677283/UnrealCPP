#include "CBTTaskNode_BossAttack.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_BossAttack::UCBTTaskNode_BossAttack()
{
	NodeName = "BossAttack";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
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
	CheckNull(character);

	float distance = character->GetDistanceTo(target);

	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;

	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, DeltaSeconds, 10));

	if (distance < character->GetAttackRange())
		character->LeftAttack();

	if (!character->IsPattern())
	{
		character->StartPattern();
		OwnerComp.GetBlackboardComponent()->SetValueAsInt("Pattern", 0);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("WaitTime", 1.0f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}