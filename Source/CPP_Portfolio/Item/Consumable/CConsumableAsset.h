#pragma once

#include "CoreMinimal.h"
#include "Item/CItemAsset.h"
#include "CConsumableAsset.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCConsumableAsset : public UCItemAsset
{
	GENERATED_BODY()
public:
	UCConsumableAsset();

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<TSubclassOf<class UCConditionEffect>> ConditionClasses;
	UPROPERTY(EditDefaultsOnly)
		TArray<float> ConditionValues;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
public:
	virtual void UseItem() override;

private:
	static TArray<class UCConditionEffect*> Conditions;
};
