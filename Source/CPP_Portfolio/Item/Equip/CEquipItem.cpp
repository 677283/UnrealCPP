#include "CEquipItem.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/Equip/CEquipItem.h"

UCEquipItem::UCEquipItem()
{
	bEquipping = false;
}

void UCEquipItem::InitializeEquipItem(EEquipType InEquipType)
{
	EquipType = InEquipType;
}

void UCEquipItem::UseItem()
{
	if (!bEquipping)
		Equip();
	else
		Unequip();

	Super::UseItem();
}


void UCEquipItem::Equip()
{
	bEquipping = true;
}

void UCEquipItem::Unequip()
{
	bEquipping = false;
}