#include "CWidget_Equip.h"
#include "Global.h"
#include "Widget/CWidget_Equip_Slot.h"
#include "Widget/CWidget_TitleBar.h"
#include "Widget/CWidget_Slot.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Blueprint/WidgetTree.h"


void UCWidget_Equip::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	bIsFocusable = true;

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);
	for (UWidget* widget : widgets)
	{
		UCWidget_Slot* slot = Cast<UCWidget_Slot>(widget);
		if (!slot) continue;

		Slots.Add(slot->GetName(), slot);
		slot->OnDataCheck.BindUObject(this, &UCWidget_Equip::OnDataCheck);
		slot->OnSlotDoubleClick.BindUObject(this, &UCWidget_Equip::OnSlotDoubleClick);
	}

}

void UCWidget_Equip::OnDataCheck(UCWidget_Slot* UpSlot, UCWidget_Slot* DownSlot)
{
	switch (DownSlot->GetSlotType())
	{
		case ESlotType::Equip:
			break;
		case ESlotType::Inventory:
			InventoryDataCheck(UpSlot, DownSlot);
			break;
	}
}

void UCWidget_Equip::InventoryDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot)
{
	if (UpSlot->GetName() == "Weapon")
	{
		UCWeaponItem* weapon = Cast<UCWeaponItem>(DownSlot->GetData());
		if (!!weapon)
		{
			weapon->UseItem();
			OnEquip_EquipWidget.ExecuteIfBound(weapon);
		}
	}
}

void UCWidget_Equip::OnSlotDoubleClick(UCWidget_Slot* InSlot)
{
	OnUnequip_EuipWidget.ExecuteIfBound(InSlot->GetName());
}

void UCWidget_Equip::OnEquipWidget(FString InSlotName, UObject* InItem)
{
	(*Slots.Find(InSlotName))->SetData(InItem);
}
