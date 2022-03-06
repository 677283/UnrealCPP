#include "CSkill_Passive.h"

UCSkill_Passive::UCSkill_Passive()
{
	SetSkillType(ESkillType::Passive);
}

void UCSkill_Passive::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	//DoSkill();
}

void UCSkill_Passive::DoSkill()
{
	Super::DoSkill();

	//TODO 버프 효과 적용
}