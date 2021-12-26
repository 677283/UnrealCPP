#include "CWidget_HUD.h"
#include "Components/PanelWidget.h"

void UCWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	MainPanel = Cast<UPanelWidget>(GetWidgetFromName("MainPanel"));
}

