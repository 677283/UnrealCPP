#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item/CItem.h"
#include "CConsumableAsset.h"
#include "CConsumableItem.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCConsumableItem : public UCItem
{
	GENERATED_BODY()

public:
	void InitializeConsumableItem(TArray<FConditionData> InDatas);

	virtual void UseItem() override;

	void EffectCondition();

	void Healing();
	void ChargeEnergy();

private:
	TArray<FConditionData> ConditionDatas;

};
