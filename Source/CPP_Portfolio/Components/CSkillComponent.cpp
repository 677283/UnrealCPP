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

UCSkill* UCSkillComponent::GetSkill(TSubclassOf<class UCSkill> InSkillClass)
{
	for (auto& skill : Skills)
	{
		CheckTrueResult(skill.Value->StaticClass() == InSkillClass, skill.Value);
	}

	return nullptr;
}

int32 UCSkillComponent::LevelCheck(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNullResult(InSkillClass, -1);
	for (auto& skill : Skills)
	{
		if (skill.Value->StaticClass() == InSkillClass)
			return skill.Value->GetSkillLevel();
	}

	return -1;
}