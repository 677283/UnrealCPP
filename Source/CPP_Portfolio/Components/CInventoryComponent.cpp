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
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

bool UCInventoryComponent::AddItem(class UCItem* InItem)
{
	int32 index = CheckSlot(InItem);
	CheckTrueResult(index == -1, false);

	Inventory[index] = InItem;

	OnAddItem.ExecuteIfBound(index, InItem);
	
	if (!!InItem)
		InItem->PickUpItem(OwnerCharacter);

	return true;
}

bool UCInventoryComponent::AddItem(int32 InIndex, class UCItem* InItem)
{
	Inventory[InIndex] = InItem;

	OnAddItem.ExecuteIfBound(InIndex, InItem);

	if (!!InItem)
		InItem->PickUpItem(OwnerCharacter);

	return true;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	CheckFalse(InIndex > -1 && InIndex < Inventory.Num());
	CheckNull(Inventory[InIndex]);

	Inventory[InIndex]->UseItem();

	UCEquipItem* equipItem = Cast<UCEquipItem>(Inventory[InIndex]);
	if (!!equipItem)


	if (!Inventory[InIndex])
		AddItem(InIndex, nullptr);

}

void UCInventoryComponent::UseItem(class UCItem* InItem)
{
	int32 index = Inventory.Find(InItem);
	CheckTrue(index == INDEX_NONE);

	Inventory[index]->UseItem();

	if (!Inventory[index])
		AddItem(index, nullptr);
}

void UCInventoryComponent::SwapItem(UObject* InItem_1, UObject* InItem_2)
{
	UCItem* item1 = Cast<UCItem>(InItem_1);
	UCItem* item2 = Cast<UCItem>(InItem_2);

	int index1 = Inventory.Find(item1);
	int index2 = Inventory.Find(item2);

	Inventory.Swap(index1, index2);
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