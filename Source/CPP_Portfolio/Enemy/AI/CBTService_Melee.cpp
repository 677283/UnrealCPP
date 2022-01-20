#include "CBTService_Melee.h"
#include "Global.h"
#include "CAIController.h"
#include "CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "Melee";
	
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent <UCBehaviorComponent>(controller);

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);

	if (state->IsStateHitted())
	{
		behavior->SetHittedMode();
		return;
	}

	ACharacter* target = behavior->GetTargetCharacter();

	if (target == NULL)
	{
		//TODO: ÆÐÆ®·Ñ

		behavior->SetWaitMode();
		return;
	}
	else 
	{
		UCStateComponent* targetState = CHelpers::GetComponent<UCStateComponent>(target);
		if (targetState->IsStateDead())
		{
			behavior->SetWaitMode();

			return;
		}
	}

	float distance = ai->GetDistanceTo(target);
	if (ai->CanAttack())
	{
		behavior->SetActionMode();

		return;
	}
	else
	{
		behavior->SetApproachMode();

		return;
	}
}