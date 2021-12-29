#include "CWidget_Slot.h"
#include "Global.h"
#include "Components/Image.h"
#include "Interfaces/ISlotWidget.h"
#include "BluePrint/WidgetTree.h"

UCWidget_Slot* UCWidget_Slot::SelectSlot = nullptr;

void UCWidget_Slot::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Visible);

	IconWidget = Cast<UImage>(GetWidgetFromName(*IconWidgetName));

}

FReply UCWidget_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);

	SelectSlot = this;

	return reply;
}

FReply UCWidget_Slot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (SelectSlot != this && !!SelectSlot)
		OnDataCheck.ExecuteIfBound(this, SelectSlot);

	SelectSlot = nullptr;

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);

	return reply;
}

FReply UCWidget_Slot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (!!SlotData)
		OnSlotDoubleClick.ExecuteIfBound(this);

	return reply;
}

void UCWidget_Slot::SetData(UObject* InData)
{
	if (!InData)
	{
		SlotData = nullptr;
		if (!!IconWidget)
			IconWidget->SetBrushFromTexture(nullptr);
		
		return;
	}
	
	SlotData = InData;
	UTexture2D* icon = nullptr;
	IISlotWidget* data = Cast<IISlotWidget>(InData);
	
	if (!!data)
		icon = data->GetIcon();

	if (!!IconWidget)
		IconWidget->SetBrushFromTexture(icon);
	
}

void UCWidget_Slot::SwapData(UCWidget_Slot* InSlot)
{
	CheckNull(InSlot);

	UObject* temp = InSlot->GetData();

	InSlot->SetData(SlotData);
	SetData(temp);
}

void UCWidget_Slot::SetIcon(class UTexture2D* InIcon)
{
	CLog::Log("SLOT IMAGE ENTER");
	CheckNull(IconWidget);
	CLog::Log("SLOT IMAGE OK");
	IconWidget->SetBrushFromTexture(InIcon);
}