#include "CWidget_InventoryDragAndDrop.h"
#include "Global.h"
#include "Components/Image.h"

void UCWidget_InventoryDragAndDrop::NativeConstruct()
{
	Super::NativeConstruct();

	Icon = Cast<UImage>(GetWidgetFromName("Icon"));
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCWidget_InventoryDragAndDrop::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushResourceObject(InIcon);
}