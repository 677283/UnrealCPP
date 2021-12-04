#include "CEquipAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/Equip/CEquipItem.h"

UCEquipAsset::UCEquipAsset()
{
	SetType(EItemType::Equip);
}

UCItem* UCEquipAsset::CreateItem(class ACharacter* InOwner, UCItem* InItem)
{
	UCEquipItem* equipItem;

	if (!InItem)
	{
		equipItem = NewObject<UCEquipItem>();
	}
	else
	{
		equipItem = Cast<UCEquipItem>(InItem);
	}

	Super::CreateItem(InOwner, equipItem);

	equipItem->InitializeEquipItem(EquipType);

	return equipItem;
}