#include "CBTTaskNode_Subjugate.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "GameFramework/Character.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTTaskNode_Subjugate::UCBTTaskNode_Subjugate()
{
	NodeName = "Subjugate";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Subjugate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI_Boss* character = Cast<ACEnemy_AI_Boss>(controller->GetPawn());

	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);
	ACharacter* target = UGameplayStatics::GetPlayerCharacter(character->GetWorld(), 0);

	float distance = character->GetDistanceTo(target);

	FRotator targetDir = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), target->GetActorLocation());
	targetDir.Pitch = 0;
	targetDir.Roll = 0;

	character->SetActorRotation(UKismetMathLibrary::RInterpTo(character->GetActorRotation(), targetDir, UGameplayStatics::GetWorldDeltaSeconds(character->GetWorld()), 10));
	character->CastSubjugate();

	return EBTNodeResult::Type::InProgress;
}

void UCBTTaskNode_Subjugate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI_Boss* character = Cast<ACEnemy_AI_Boss>(controller->GetPawn());

	if (!character->IsPattern())
	{
		character->StartPattern();
		OwnerComp.GetBlackboardComponent()->SetValueAsInt("Pattern", 0);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("WaitTime", 1.0f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}