#include "CWidget_Equip.h"
#include "Global.h"
#include "Widget/CWidget_Equip_Slot.h"
#include "Blueprint/WidgetTree.h"

void UCWidget_Equip::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);
	for (UWidget* widget : widgets)
	{
		UCWidget_Equip_Slot* slot = Cast<UCWidget_Equip_Slot>(widget);
		if (!slot) continue;
		Slots.Add(slot->GetName(), slot);
		slot->OnSlotMouseButtonDouble.BindUObject(this, &UCWidget_Equip::OnSlotMouseButtonDouble);
	}

	bIsFocusable = true;
}

void UCWidget_Equip::SetSlotIcon(FString InName, UTexture2D* InIcon)
{
	(*Slots.Find(InName))->SetIcon(InIcon);
}

void UCWidget_Equip::OnSlotMouseButtonDouble(FString InName)
{
	OnEquipAction.ExecuteIfBound(InName);
	(*Slots.Find(InName))->SetIcon(nullptr);
}
