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

	SetItem(index, InItem);
	InItem->PickUpItem(OwnerCharacter);

	return true;
}

void UCInventoryComponent::UseItem(int32 InIndex)
{
	CheckNull(Inventory[InIndex]);
	CheckFalse(InIndex > -1 && InIndex < Inventory.Num());

	Inventory[InIndex]->UseItem();

	if (!Inventory[InIndex])
		SetItem(InIndex, nullptr);

}

void UCInventoryComponent::SwapItem(int32 InIndex_1, int32 InIndex_2)
{
	CheckTrue(!Inventory[InIndex_1] && !Inventory[InIndex_2]);
	UCItem* temp = Inventory[InIndex_1];

	SetItem(InIndex_1, Inventory[InIndex_2]);
	SetItem(InIndex_2, temp);
}

void UCInventoryComponent::OnEquip(UCItem* InEquipItem, UCItem* InUnequipItem)
{
	int32 index = Inventory.Find(InEquipItem);

	CheckTrue(index == INDEX_NONE);

	if (!!InUnequipItem)
		Cast<UCEquipItem>(InUnequipItem)->Unequip();
	SetItem(index, InUnequipItem);
}

void UCInventoryComponent::OnUnequip(UCItem* InEquipItem, UCItem* InUnequipItem)
{
	CheckNull(InUnequipItem);
	Cast<UCEquipItem>(InUnequipItem)->Unequip();
	AddItem(InUnequipItem);
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

void UCInventoryComponent::SetItem(int32 InIndex, class UCItem* InItem)
{
	Inventory[InIndex] = InItem;
	UTexture2D* icon;

	!!InItem ? icon = InItem->GetIcon() : icon = nullptr;
	OnUpdateIcon.ExecuteIfBound(InIndex, icon);
}