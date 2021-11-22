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