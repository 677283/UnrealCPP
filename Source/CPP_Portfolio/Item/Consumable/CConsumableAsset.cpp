#include "CConsumableAsset.h"
#include "Global.h"
#include "CConditionEffect.h"

TArray<UCConditionEffect*> UCConsumableAsset::Conditions;

UCConsumableAsset::UCConsumableAsset()
{
	
}

void UCConsumableAsset::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	for (TSubclassOf<UCConditionEffect> condition : ConditionClasses)
	{
		Conditions.Add(NewObject<UCConditionEffect>(this, condition));
	}
}

void UCConsumableAsset::UseItem()
{
	Super::UseItem();
	
	for (int32 i = 0; i<Conditions.Num(); i++)
	{
		Conditions[i]->AddCondition(OwnerCharacter, ConditionValues[i]);
	}
}