#include "CConsumableAsset.h"
#include "Global.h"
#include "Item/Consumable/CConsumableItem.h"

UCConsumableAsset::UCConsumableAsset()
{
	
}

UCItem* UCConsumableAsset::CreateItem(class ACharacter* InOwner, class UCItem* InItem)
{
	UCConsumableItem* consumableItem;

	if (!InItem)
	{
		consumableItem = NewObject<UCConsumableItem>();
	}
	else
	{
		consumableItem = Cast<UCConsumableItem>(InItem);
	}
	Super::CreateItem(InOwner, consumableItem);

	consumableItem->InitializeConsumableItem(ConditionDatas);

	return consumableItem;
}