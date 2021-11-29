#include "CWidget_InventorySlot.h"
#include "Global.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UCWidget_InventorySlot::NativeConstruct()
{
	Icon = Cast<UImage>(GetWidgetFromName("Icon"));
	
	FString str = GetName();
	TArray<FString> arr;
	str.ParseIntoArray(arr, L"_");
	Index = FCString::Atoi(*arr.Last());
}

FReply UCWidget_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetCaptureMouseOnClick(EMouseCaptureMode::NoCapture);

	if (OnSlotPressed.IsBound())
		OnSlotPressed.Broadcast(Index);

	return reply;
}

FReply UCWidget_InventorySlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	   
	if (OnSlotReleased.IsBound())
		OnSlotReleased.Broadcast(Index);

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);

	return reply;
}

FReply UCWidget_InventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (OnSlotDoubleClick.IsBound())
		OnSlotDoubleClick.Broadcast(Index);

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetCaptureMouseOnClick(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);

	return reply;
}

void UCWidget_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (OnSlotHoverd.IsBound())
		OnSlotHoverd.Broadcast(Index);

}
void UCWidget_InventorySlot::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushFromTexture(InIcon);
}