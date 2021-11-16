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
	Skills.Add(InSkill->GetName(), InSkill);
}