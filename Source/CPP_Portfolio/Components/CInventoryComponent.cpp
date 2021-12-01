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
	int32 index = CheckSlot(InItem);
	CheckTrueResult(index == -1, false);

	Inventory[index] = InItem;

	InItem->PickUpItem(OwnerCharacter);

	if (OnInventoryUpdate.IsBound())
		OnInventoryUpdate.Broadcast();

	return true;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	CheckNull(Inventory[InIndex]);
	CLog::Log("In InvenComponent");
	Inventory[InIndex]->UseItem();

	CheckNull(Inventory[InIndex]);
	if (Inventory[InIndex]->GetAmount() < 1)
	{
		Inventory[InIndex]->DestroyItem();
		Inventory[InIndex] = NULL;

		if (OnInventoryUpdate.IsBound())
			OnInventoryUpdate.Broadcast();
	}
}

void UCInventoryComponent::SwapItem(int32 InIndex_1, int32 InIndex_2)
{
	CheckTrue(!Inventory[InIndex_1] && !Inventory[InIndex_2]);
	UCItemAsset* temp = Inventory[InIndex_1];
	Inventory[InIndex_1] = Inventory[InIndex_2];
	Inventory[InIndex_2] = temp;
}

void UCInventoryComponent::OnEquip(class UCItemAsset* InItem)
{
	int32 index = Inventory.Find(InItem);

	CheckTrue(index == INDEX_NONE);

	Inventory[index] = NULL;

	if (OnInventoryUpdate.IsBound())
		OnInventoryUpdate.Broadcast();
}

void UCInventoryComponent::OnUnequip(class UCItemAsset* InItem)
{

}

int32 UCInventoryComponent::CheckSlot(UCItemAsset* InItem)
{
	for (int32 i = 0; i<Inventory.Num(); i++)
	{
		if (Inventory[i] == NULL)
			continue;
		if (Inventory[i]->GetItemName().Compare(InItem->GetItemName()) == 0)
		{
			int32 remain = Inventory[i]->AddAmount(InItem->GetAmount());

			if (remain == 0)
			{
				InItem->DestroyItem();
				return -1;
			}	
		}
	}
	
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] == NULL)
			return i;
	}

	return -1;
}