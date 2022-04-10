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

float UCStatusComponent::SetLife(float InValue)
{
	CurrentLife += InValue;

	if (CurrentLife > Life)
		CurrentLife = Life;

	return CurrentLife;
}

void UCStatusComponent::Hitted()
{
	bHitable = false;
	CheckEndureTime = EndureTime;
	GetOwner()->GetWorld()->GetTimerManager().SetTimer(EndureTimerHandle,this,&UCStatusComponent::CheckEndureTimer, GetOwner()->GetWorld()->DeltaTimeSeconds, true);
}

void UCStatusComponent::CheckEndureTimer()
{
	CheckEndureTime -= GetOwner()->GetWorld()->DeltaTimeSeconds;

	if (CheckEndureTime)
	{
		bHitable = true;
		GetOwner()->GetWorld()->GetTimerManager().ClearTimer(EndureTimerHandle);
	}
}