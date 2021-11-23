#include "CEquipment.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"

void UCEquipment::BeginPlay(class ACharacter* InOwner)
{
	CheckNull(InOwner);

	OwnerCharacter = InOwner;
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
}

void UCEquipment::SetOwnerCharacter(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;

	if (!!InOwner)
		State = CHelpers::GetComponent<UCStateComponent>(InOwner);
	else
		State = NULL;
}