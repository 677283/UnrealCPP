#include "CSkill.h"
#include "GameFramework/Character.h"

void UCSkill::BeginPlay(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}

