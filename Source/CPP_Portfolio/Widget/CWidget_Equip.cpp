#include "CWidget_Equip.h"
#include "Global.h"
#include "Widget/CWidget_Equip_Slot.h"

void UCWidget_Equip::NativeConstruct()
{
	Super::NativeConstruct();

	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Helmet")));
	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Top")));
	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Bottoms")));
	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Weapon")));
	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Weapon_Sub")));
	Slots.Add(Cast<UCWidget_Equip_Slot>(GetWidgetFromName("Boot")));

	bIsFocusable = true;
}

void UCWidget_Equip::SetSlotIcon(EEquipSlot InIndex, UTexture2D* InIcon)
{
	Slots[(uint8)InIndex]->SetIcon(InIcon);
}

