#include "CWidget_Equip_Slot.h"
#include "Global.h"
#include "Components/Image.h"

void UCWidget_Equip_Slot::NativeConstruct()
{
	Icon = Cast<UImage>(GetWidgetFromName("Icon"));
}

FReply UCWidget_Equip_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	CLog::Log("EQUIP SLOT DOWN");

	OnSlotMouseButtonDown.ExecuteIfBound(GetName());

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);

	return reply;
}

FReply UCWidget_Equip_Slot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	OnSlotMouseButtonUp.ExecuteIfBound(GetName());

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);

	return reply;
}

FReply UCWidget_Equip_Slot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	OnSlotMouseButtonDouble.ExecuteIfBound(GetName());

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);

	return reply;
}

void UCWidget_Equip_Slot::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushFromTexture(InIcon);
}

