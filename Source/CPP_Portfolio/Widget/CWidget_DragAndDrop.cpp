#include "CWidget_DragAndDrop.h"
#include "Global.h"
#include "Components/Image.h"

void UCWidget_DragAndDrop::NativeConstruct()
{
	Super::NativeConstruct();

	Icon = Cast<UImage>(GetWidgetFromName("Icon"));
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCWidget_DragAndDrop::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushResourceObject(InIcon);
}