#include "CWidget_QuickSlot.h"
#include "Global.h"
#include "Widget/CWidget_Slot.h"
#include "Blueprint/WidgetTree.h"
#include "Interfaces/ISlotWidget.h"

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
	IISlotWidget* slotData = Cast<IISlotWidget>(Slots[InIndex]->GetData());
	
	CheckNull(slotData);

	slotData->ActiveSlot();
}

void UCWidget_QuickSlot::OnDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot)
{
	UpSlot->SwapData(DownSlot);
}