#include "CBTTaskNode_SetSpeed.h"
#include "Global.h"
#include "Enemy/AI/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCBTTaskNode_SetSpeed::UCBTTaskNode_SetSpeed()
{
	NodeName = "SetSpeed";
}

EBTNodeResult::Type UCBTTaskNode_SetSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	ACharacter* character = Cast<ACharacter>(controller->GetPawn());

	UCharacterMovementComponent* movement = CHelpers::GetComponent<UCharacterMovementComponent>(character);

	//movement->MaxWalkSpeed = 

	return EBTNodeResult::Type::Succeeded;
}

