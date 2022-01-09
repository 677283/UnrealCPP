#pragma once

#include "CoreMinimal.h"
#include "Item/CItemAsset.h"
#include "CConsumableAsset.generated.h"

UENUM(BlueprintType)
enum class EConditionType : uint8
{
	Healing, ChargeEnergy, AmorUp, Max
};

USTRUCT(BlueprintType)
struct FConditionData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		EConditionType Condition;

	UPROPERTY(EditDefaultsOnly, NoClear)
		float Value;

	UPROPERTY(EditDefaultsOnly)
		float Time;
};

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCConsumableAsset : public UCItemAsset
{
	GENERATED_BODY()
public:
	UCConsumableAsset();

private:
	UPROPERTY(EditDefaultsOnly, NoClear)
		TArray<FConditionData> ConditionDatas;

public:
	virtual class UCItem* CreateItem(class ACharacter* InOwner, class UCItem* InItem) override;

};
