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
	CurrentMana = Mana += Energy * 10;
}

bool UCStatusComponent::GetCriticalChance()
{
	float rnd = FMath::RandRange(0, 1);

	if (Critical * 0.01 <= rnd)
		return true;
	else
		return false;
}

void UCStatusComponent::SetLife(float InValue)
{
	CurrentLife += InValue;

	if (CurrentLife > Life)
		CurrentLife = Life;
	else if (CurrentLife <= 0)
	{
		if (OnDeath.IsBound())
			OnDeath.Broadcast();
	}
	
}