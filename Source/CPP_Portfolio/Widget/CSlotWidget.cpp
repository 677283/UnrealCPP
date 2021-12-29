#include "CSlotWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Interfaces/ISlotWidget.h"
#include "BluePrint/WidgetTree.h"

UCSlotWidget* UCSlotWidget::SelectSlot = nullptr;

void UCSlotWidget::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Visible);

	IconWidget = Cast<UImage>(GetWidgetFromName(*IconWidgetName));

}

FReply UCSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);

	SelectSlot = this;

	return reply;
}

FReply UCSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (SelectSlot != this)
		OnDataCheck.ExecuteIfBound(this, SelectSlot);

	SelectSlot = nullptr;

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);

	return reply;
}

void UCSlotWidget::SetData(UObject* InData)
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

void UCSlotWidget::SwapData(UCSlotWidget* InSlot)
{
	CheckNull(InSlot);

	UObject* temp = InSlot->GetData();

	InSlot->SetData(SlotData);
	SetData(temp);
}

void UCSlotWidget::SetIcon(class UTexture2D* InIcon)
{
	CLog::Log("SLOT IMAGE ENTER");
	CheckNull(IconWidget);
	CLog::Log("SLOT IMAGE OK");
	IconWidget->SetBrushFromTexture(InIcon);
}