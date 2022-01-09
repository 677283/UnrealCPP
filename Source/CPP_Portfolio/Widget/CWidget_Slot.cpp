#include "CWidget_Slot.h"
#include "Global.h"
#include "Components/Image.h"
#include "Interfaces/ISlotWidget.h"
#include "BluePrint/WidgetTree.h"
#include "Widget/CWidget_DragAndDrop.h"

UCWidget_Slot* UCWidget_Slot::SelectSlot = nullptr;
UCWidget_DragAndDrop* UCWidget_Slot::DragAndDrop = nullptr;

void UCWidget_Slot::NativeConstruct()
{
	SetVisibility(ESlateVisibility::Visible);

	IconWidget = Cast<UImage>(GetWidgetFromName(*IconWidgetName));

	if (!DragAndDrop)
	{
		DragAndDropClass = CHelpers::GetClassDynamic<UCWidget_DragAndDrop>("WidgetBlueprint'/Game/__ProjectFile/Widgets/WB_DragAndDrop.WB_DragAndDrop_C'");
		DragAndDrop = CreateWidget<UCWidget_DragAndDrop, APlayerController>(GetOwningPlayer(), DragAndDropClass, "DragAndDrop");
		DragAndDrop->SetVisibility(ESlateVisibility::Hidden);
		DragAndDrop->AddToViewport(444);
	}
}

void UCWidget_Slot::NativeDestruct()
{
	Super::NativeDestruct();

	SelectSlot = nullptr;
	DragAndDrop = nullptr;
}

FReply UCWidget_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == FKey("RightMouseButton"))
	{
		//CLog::Log("Right Test");
		OnSlotRightClick.ExecuteIfBound(this);
	}
	else
	{
		if (!!SlotData)
		{
			UGameViewportClient* Viewport = GEngine->GameViewport;
			Viewport->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);

			SelectSlot = this;
			DragAndDrop->SetActive(true);

			IISlotWidget* data = Cast<IISlotWidget>(SlotData);
			if (!!data)
				DragAndDrop->SetIcon(data->GetIcon());
		}
	}
	return reply;
}

FReply UCWidget_Slot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (SelectSlot != this && !!SelectSlot)
		OnDataCheck.ExecuteIfBound(this, SelectSlot);

	SelectSlot = nullptr;
	DragAndDrop->SetActive(false);

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
	SlotData = InData;
	UTexture2D* icon = nullptr;
	IISlotWidget* data = Cast<IISlotWidget>(InData);
	
	if (!!data)
		icon = data->GetIcon();

	SetIcon(icon);
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
	CheckNull(IconWidget);
	IconWidget->SetBrushFromTexture(InIcon);
}