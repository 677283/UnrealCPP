#include "CSkill_Active.h"
#include "Global.h"

UCSkill_Active::UCSkill_Active()
{
	SetSkillType(ESkillType::Active);
}

void UCSkill_Active::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
}