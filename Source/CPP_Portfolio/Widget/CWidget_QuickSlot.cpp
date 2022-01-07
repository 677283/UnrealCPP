#include "CWidget_QuickSlot.h"
#include "Global.h"
#include "Widget/CWidget_Slot.h"
#include "Blueprint/WidgetTree.h"
#include "Interfaces/ISlotWidget.h"
#include "Item/CItem.h"

void UCWidget_QuickSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);

	TArray<UWidget*> widgets;

	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_Slot* slot = Cast<UCWidget_Slot>(widget);
		
		if (!slot) continue;

		Slots.Add(slot);
		slot->OnDataCheck.BindUObject(this, &UCWidget_QuickSlot::OnDataCheck);
	}
}

void UCWidget_QuickSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

void UCWidget_QuickSlot::ActiveSlot(int32 InIndex)
{
	CheckTrue(InIndex < 0 || InIndex > Slots.Num());
	CheckNull(Slots[InIndex]->GetData());

	IISlotWidget* slotData = Cast<IISlotWidget>(Slots[InIndex]->GetData());
	
	CheckNull(slotData);

	slotData->ActiveSlot();
}

void UCWidget_QuickSlot::OnDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot)
{
	CheckNull(DownSlot);
	switch (DownSlot->GetSlotType())
	{
	case ESlotType::Inventory:
		InventoryDataCheck(UpSlot, DownSlot);
		break;
	case ESlotType::Equip:
		//EquipDataCheck(UpSlot, DownSlot);
		break;
	case ESlotType::SkillTree:
		SkillTreeDataCheck(UpSlot, DownSlot);
		break;
	}
}

void UCWidget_QuickSlot::InventoryDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot)
{
	UCItem* item = Cast<UCItem>(DownSlot->GetData());

	CheckFalse(item->GetItemType() == EItemType::Consumable);

	UpSlot->SetData(item);

}

void UCWidget_QuickSlot::SkillTreeDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot)
{
	for (UCWidget_Slot* slot : Slots)
	{
		if (slot->GetData() == DownSlot->GetData())
		{
			slot->SetData(nullptr);
			break;
		}
	}

	UpSlot->SetData(DownSlot->GetData());
}