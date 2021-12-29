#include "CSlotWidget.h"
#include "Global.h"
#include "Components/Image.h"
#include "Interfaces/ISlotWidget.h"
#include "BluePrint/WidgetTree.h"

UCSlotWidget* UCSlotWidget::SelectData = nullptr;

void UCSlotWidget::NativeConstruct()
{
	IconWidget = Cast<UImage>(GetWidgetFromName(*IconWidgetName));
}

FReply UCSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	SelectData = this;

	return reply;
}

FReply UCSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	OnDataCheck.ExecuteIfBound(this, SelectData);

	SelectData = nullptr;

	return reply;
}

void UCSlotWidget::SetData(UObject* InData)
{
	if (!InData)
	{
		SlotData = nullptr;
		if (!!IconWidget)
			IconWidget->SetBrushFromTexture(nullptr);

		OnSetData.ExecuteIfBound(InData);

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
	CheckNull(IconWidget);
	IconWidget->SetBrushFromTexture(InIcon);
}