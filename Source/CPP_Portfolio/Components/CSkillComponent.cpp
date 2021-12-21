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
	InSkill->BeginPlay(Cast<ACharacter>(GetOwner()));
	Skills.Add(InSkill->GetSkillName(), InSkill);
}

UCSkill* UCSkillComponent::GetSkill(FName InSkillName)
{
	if (!Skills.Find(InSkillName)) return nullptr;
	return *(Skills.Find(InSkillName));
}

UCSkill* UCSkillComponent::GetSkill(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNullResult(InSkillClass, nullptr);
	for (auto& skill : Skills)
	{
		if(InSkillClass->IsChildOf(skill.Value->GetClass()))
			return skill.Value;
	}

	return nullptr;
}

int32 UCSkillComponent::LevelCheck(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNullResult(InSkillClass, -1);
	for (auto& skill : Skills)
	{
		if (InSkillClass->IsChildOf(skill.Value->GetClass()))
			return skill.Value->GetSkillLevel();
	}

	return -1;
}

void UCSkillComponent::SkillLevelUp(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNull(InSkillClass);

	GetSkill(InSkillClass)->SkillLevelUp();
	SkillPoint--;
}