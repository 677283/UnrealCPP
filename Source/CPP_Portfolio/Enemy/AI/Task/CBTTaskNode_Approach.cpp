#include "CBTTaskNode_Approach.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"

UCBTTaskNode_Approach::UCBTTaskNode_Approach()
{
	NodeName = "Approach";
	bNotifyTick = true;
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
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACEnemy_AI_Boss* boss = Cast<ACEnemy_AI_Boss>(character);
	
	ACharacter* target;
	if(!!boss)
		target = UGameplayStatics::GetPlayerCharacter(boss->GetWorld(), 0);
	else
		target = behavior->GetTargetCharacter();

	CheckNull(target);

	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;
	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, DeltaSeconds, 10));
	character->MoveForward(1);

	if ((target->GetActorLocation() - character->GetActorLocation()).Size() < 250)
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
}