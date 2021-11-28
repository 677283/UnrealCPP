#include "CInventoryComponent.h"
#include "Global.h"
#include "Item/CItemAsset.h"
#include "GameFramework/Character.h"

UCInventoryComponent::UCInventoryComponent()
{
	
}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Inventory.SetNum(InventorySize);
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

bool UCInventoryComponent::AddItem(class UCItemAsset* InItem)
{
	int32 index = EmptySlotCheck();
	CLog::Log(index);
	CheckTrueResult(index == -1, false);

	Inventory[index] = InItem;

	if (OnAddItem.IsBound())
		OnAddItem.Broadcast();
	InItem->PickUpItem(OwnerCharacter);
	return true;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	Inventory[InIndex]->UseItem();
}

void UCInventoryComponent::SwapItem(int32 InIndex_1, int32 InIndex_2)
{
	CheckTrue(!Inventory[InIndex_1] && !Inventory[InIndex_2]);
	CLog::Log("Swap");
	UCItemAsset* temp = Inventory[InIndex_1];
	Inventory[InIndex_1] = Inventory[InIndex_2];
	Inventory[InIndex_2] = temp;
}

int32 UCInventoryComponent::EmptySlotCheck()
{
	CLog::Log(Inventory.Num());
	for (int32 i = 0; i<Inventory.Num(); i++)
	{
		if (!Inventory[i])
			return i;
	}

	return -1;
}