#include "CWidget_QuickSlot.h"
#include "Global.h"
#include "Components/Image.h"

void UCWidget_QuickSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UImage* gauge = Cast<UImage>(GetWidgetFromName("Gauge"));

	CheckNull(gauge);

	gauge->GetDynamicMaterial()->SetScalarParameterValue("GaugePercent", 0.5f);

}