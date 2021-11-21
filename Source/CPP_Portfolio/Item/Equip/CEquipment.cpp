#include "CEquipment.h"

void UCEquipment::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
}