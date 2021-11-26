#include "CInventoryComponent.h"
#include "Global.h"
#include "Item/CItemAsset.h"

UCInventoryComponent::UCInventoryComponent()
{
	Inventory.SetNum(InventorySize);
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCInventoryComponent::AddItem(class UCItemAsset* InItem)
{
	int32 index = SlotCheck();
	CheckTrue(index == -1);

	Inventory[index] = InItem;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	Inventory[InIndex]->UseItem();
}

int32 UCInventoryComponent::SlotCheck()
{
	for (int32 i = 0; i<Inventory.Num(); i++)
	{
		if (!Inventory[i])
			return i;
	}

	return -1;
}