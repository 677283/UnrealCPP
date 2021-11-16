#include "CSkillComponent.h"
#include "Global.h"
#include "Skill/CSkill.h"

UCSkillComponent::UCSkillComponent()
{

}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCSkillComponent::AddSkill(class UCSkill* InSkill)
{
	CheckNull(InSkill);

	Skills.Add(InSkill->GetSkillName(), InSkill);
}

UCSkill* UCSkillComponent::GetSkill(FName InSkillName)
{
	return *(Skills.Find(InSkillName));
}