#include "CSkillComponent.h"

UCSkillComponent::UCSkillComponent()
{

}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCSkillComponent::AddSkill(class CSkill* InSkill)
{
	Skills.Add(InSkill->Get)
}