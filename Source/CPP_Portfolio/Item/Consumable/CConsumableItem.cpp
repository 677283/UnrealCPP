#include "CConsumableItem.h"
#include "Global.h"

void UCConsumableItem::InitializeConsumableItem(TArray<FConditionData> InDatas)
{
	ConditionDatas = InDatas;

}

void UCConsumableItem::UseItem()
{
	Amount--;
	EffectCondition();

	Super::UseItem();
}

void UCConsumableItem::EffectCondition()
{

	for (FConditionData conditionData : ConditionDatas)
	{
		switch (conditionData.Condition)
		{
			case EConditionType::Healing:
				Healing();
				break;

			case EConditionType::ChargeEnergy:

				break;
		}
	}
}

void UCConsumableItem::Healing()
{

}

void UCConsumableItem::ChargeEnergy()
{

}