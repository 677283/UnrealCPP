#include "CBTService_Melee.h"
#include "Global.h"
#include "CAIController.h"
#include "CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CEquipComponent.h"

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
	UCEquipComponent* weapon = CHelpers::GetComponent<UCEquipComponent>(ai);

	if (target == NULL)
	{
		//TODO: ��Ʈ��
		if (weapon->IsHandsOn())
		{
			ai->UnequipWeapon();
		}
		behavior->SetPatrolMode();
		//behavior->SetWaitMode();
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

	if (!weapon->IsHandsOn())
	{
		CLog::Log("EQUIP");
		ai->EquipWeapon();
	}
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