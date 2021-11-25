#include "CInventoryComponent.h"
#include "Global.h"
#include "Item/CItemAsset.h"

UCInventoryComponent::UCInventoryComponent()
{
	//Inventory.SetNum(InventorySize);
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCInventoryComponent::AddItem(class UCItemAsset* InItem)
{
	CheckTrue(Inventory.Num() >= InventorySize);

	Inventory.Add(InItem);

}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	Inventory[InIndex]->UseItem();
}