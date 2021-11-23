#include "CDoAction.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/InputSettings.h"

UCDoAction::UCDoAction()
{
	bComboEnable = false;
}

void UCDoAction::BeginPlay(class ACharacter* InOwner)
{
	CheckNull(InOwner);

	OwnerCharacter = InOwner;
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
}

void UCDoAction::OnEquipActorCollision()
{
	HittedCharacters.Empty();
}

void UCDoAction::SetOwnerCharacter(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;

	if (!!InOwner)
		State = CHelpers::GetComponent<UCStateComponent>(InOwner);
	else
		State = NULL;
}