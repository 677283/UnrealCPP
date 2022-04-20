#include "CBTService_Boss.h"
#include "Global.h"
#include "CAIController.h"
#include "CEnemy_AI_Boss.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBTService_Boss::UCBTService_Boss()
{
	NodeName = "Boss";
}

void UCBTService_Boss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent <UCBehaviorComponent>(controller);

	ACEnemy_AI_Boss* ai = Cast<ACEnemy_AI_Boss>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);

	if (state->IsStateHitted())
	{
		behavior->SetHittedMode();
		return;
	}

	int pattern = OwnerComp.GetBlackboardComponent()->GetValueAsInt("Pattern");
	
	//OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", UGameplayStatics::GetPlayerCharacter(ai->GetWorld(),0));

	if (pattern == 0)
	{
		//TODO : 패턴 선택.
		pattern = UKismetMathLibrary::RandomInteger(4) + 1;
		
		OwnerComp.GetBlackboardComponent()->SetValueAsInt("Pattern", pattern);
		return;
	}
}