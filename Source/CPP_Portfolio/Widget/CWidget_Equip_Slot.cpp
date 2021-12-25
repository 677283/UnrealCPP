#include "CWidget_Equip_Slot.h"
#include "Components/Image.h"

void UCWidget_Equip_Slot::NativeConstruct()
{
	Icon = Cast<UImage>(GetWidgetFromName("Icon"));
}

void UCWidget_Equip_Slot::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushFromTexture(InIcon);
}

