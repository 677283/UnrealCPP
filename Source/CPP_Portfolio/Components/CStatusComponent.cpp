#include "CStatusComponent.h"
#include "Skill/CSkill.h"
#include "Item/CItemAsset.h"

UCStatusComponent::UCStatusComponent()
{

}


void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentLife = Life += Vitality * 10;
}

bool UCStatusComponent::GetCriticalChance()
{
	float rnd = FMath::RandRange(0, 1);

	if (Critical * 0.01 <= rnd)
		return true;
	else
		return false;
}

void UCStatusComponent::AddSkillBuff(CSkill* InSkill)
{
	
}

void UCStatusComponent::AddItemBuff(CItem* InItem)
{

}