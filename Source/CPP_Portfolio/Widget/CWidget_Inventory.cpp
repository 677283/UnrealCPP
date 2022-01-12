#include "CWidget_Inventory.h"
#include "Global.h"
#include "Item/CItemAsset.h"
#include "Widget/CWidget_InventorySlot.h"
#include "Widget/CWidget_InventoryDragAndDrop.h"
#include "Widget/CWidget_Slot.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

#include "Widget/CWidget_TitleBar.h"

void UCWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	//Base Setting
	{
		SetVisibility(ESlateVisibility::Hidden);
		bIsFocusable = true;
	}

	//Slot Setting
	{
		TArray<UWidget*> widgets;
		WidgetTree->GetAllWidgets(widgets);

		for (UWidget* widget : widgets)
		{
			UCWidget_Slot* slot = Cast<UCWidget_Slot>(widget);
			if (!!slot)
			{
				Slots.Add(slot);
				slot->OnDataCheck.BindUObject(this, &UCWidget_Inventory::OnDataCheck);
				slot->OnSlotDoubleClick.BindUObject(this, &UCWidget_Inventory::OnSlotDoubleClick);
			}
		}
	}
}
void UCWidget_Inventory::OnSlotDoubleClick(UCWidget_Slot* InSlot)
{
	OnUseItem.ExecuteIfBound(Cast<UCItem>(InSlot->GetData()));
}

void UCWidget_Inventory::OnDataCheck(UCWidget_Slot* UpSlot, UCWidget_Slot* DownSlot)
{
	CheckNull(DownSlot);
	switch (DownSlot->GetSlotType())
	{
		case ESlotType::Inventory:
			InventoryDataCheck(UpSlot, DownSlot);
			break;
		case ESlotType::Equip:
			EquipDataCheck(UpSlot, DownSlot);
			break;
		case ESlotType::QuickSlot:
			QuickSlotDataCheck(UpSlot, DownSlot);
			break;
	}
}

void UCWidget_Inventory::InventoryDataCheck(UCWidget_Slot* UpSlot, UCWidget_Slot* DownSlot)
{
	CheckNull(DownSlot->GetData());

	DownSlot->SwapData(UpSlot);
	OnSwapItem.ExecuteIfBound(Slots.Find(UpSlot), Slots.Find(DownSlot));
}

void UCWidget_Inventory::EquipDataCheck(UCWidget_Slot* UpSlot, UCWidget_Slot* DownSlot)
{
	OnUnequip_InvenWidget.ExecuteIfBound(DownSlot->GetName());
}

void UCWidget_Inventory::QuickSlotDataCheck(UCWidget_Slot* UpSlot, UCWidget_Slot* DownSlot)
{

}

void UCWidget_Inventory::OnAddItem(int32 InIndex, UObject* InItem)
{
	CheckFalse(Slots.Num() > InIndex);
	Slots[InIndex]->SetData(InItem);
}

void UCWidget_Inventory::OnSlotUpdate(int32 InIndex, UCItem* InItem)
{
	CheckFalse(Slots.Num() > InIndex);
	//TODO 슬롯 업데이트
}
