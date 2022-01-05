#include "CInventoryComponent.h"
#include "Global.h"
#include "Item/CItem.h"
#include "Item/Equip/CEquipItem.h"
#include "GameFramework/Character.h"
#include "Widget/CWidget_Inventory.h"
#include "Widget/CWidget_HUD.h"
#include "Player/CPlayer.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"

UCInventoryComponent::UCInventoryComponent()
{

}

void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Inventory.SetNum(InventorySize);
	UpdateDelegateHandles.SetNum(InventorySize);
	DestroyDelegateHandles.SetNum(InventorySize);
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

//아이템창 비울때도 AddItem을 이용
bool UCInventoryComponent::AddItem(UCItem* InItem)
{
	int32 index = CheckSlot(InItem);
	CheckTrueResult(index == -1, false);

	if (!!Inventory[index])
	{
		Inventory[index]->OnUpdateItem.Remove(UpdateDelegateHandles[index]);
		Inventory[index]->OnDestroyItem.Remove(DestroyDelegateHandles[index]);
	}

	Inventory[index] = InItem;

	OnAddItem.ExecuteIfBound(index, InItem);
	
	if (!!InItem)
	{
		InItem->PickUpItem(OwnerCharacter);
		UpdateDelegateHandles[index] = InItem->OnUpdateItem.AddUObject(this, &UCInventoryComponent::OnUpdateItem);
		DestroyDelegateHandles[index] = InItem->OnDestroyItem.AddUObject(this, &UCInventoryComponent::OnDestroyItem);
	}

	return true;
}

bool UCInventoryComponent::AddItem(int32 InIndex, UCItem* InItem)
{
	if (!!Inventory[InIndex])
	{
		Inventory[InIndex]->OnUpdateItem.Remove(UpdateDelegateHandles[InIndex]);
		Inventory[InIndex]->OnDestroyItem.Remove(DestroyDelegateHandles[InIndex]);
	}

	Inventory[InIndex] = InItem;

	OnAddItem.ExecuteIfBound(InIndex, InItem);

	if (!!InItem)
		InItem->PickUpItem(OwnerCharacter);

	if (!!InItem)
	{
		InItem->PickUpItem(OwnerCharacter);
		UpdateDelegateHandles[InIndex] = InItem->OnUpdateItem.AddUObject(this, &UCInventoryComponent::OnUpdateItem);
		DestroyDelegateHandles[InIndex] = InItem->OnDestroyItem.AddUObject(this, &UCInventoryComponent::OnDestroyItem);
	}

	return true;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	CheckFalse(InIndex > -1 && InIndex < Inventory.Num());
	CheckNull(Inventory[InIndex]);

	Inventory[InIndex]->UseItem();

	UCEquipItem* equipItem = Cast<UCEquipItem>(Inventory[InIndex]);
	if (!!equipItem)
	{
		OnEquipInventory.ExecuteIfBound(equipItem);
	}

}

void UCInventoryComponent::UseItem(UCItem* InItem)
{
	int32 index = Inventory.Find(InItem);
	CheckTrue(index == INDEX_NONE);

	Inventory[index]->UseItem();

	UCEquipItem* equipItem = Cast<UCEquipItem>(Inventory[index]);
	if (!!equipItem)
	{
		OnEquipInventory.ExecuteIfBound(equipItem);
	}

}

void UCInventoryComponent::SwapItem(int32 InIndex_1, int32 InIndex_2)
{
	Inventory.Swap(InIndex_1, InIndex_2);
}

void UCInventoryComponent::OnEquip(UCItem* InEquipItem, UCItem* InUnequipItem)
{
	int32 index = Inventory.Find(InEquipItem);

	CheckTrue(index == INDEX_NONE);

	if (!!InUnequipItem)
		Cast<UCEquipItem>(InUnequipItem)->Unequip();

	AddItem(index, InUnequipItem);
}

bool UCInventoryComponent::OnUnequip(UCItem* InUnequipItem)
{
	CheckFalseResult(AddItem(InUnequipItem), false);
	Cast<UCEquipItem>(InUnequipItem)->Unequip();
	return true;
}

void UCInventoryComponent::OnUpdateItem(UCItem * InItem)
{
	int32 index = Inventory.Find(InItem);

	CheckTrue(index == INDEX_NONE);

	OnSlotUpdate.ExecuteIfBound(index, InItem);
}

void UCInventoryComponent::OnDestroyItem(UCItem* InItem)
{
	int32 index = Inventory.Find(InItem);

	CheckTrue(index == INDEX_NONE);

	OnSlotUpdate.ExecuteIfBound(index, nullptr);
	Inventory[index] = nullptr;
}

int32 UCInventoryComponent::CheckSlot(UCItem* InItem)
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