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
	CLog::Log("Press");
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (OnSlotPressed.IsBound())
		OnSlotPressed.Broadcast(Index);
	return reply;
}

FReply UCWidget_InventorySlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CLog::Log("Release");
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	   
	if (OnSlotReleased.IsBound())
		OnSlotReleased.Broadcast(Index);

	return reply;
}

FReply UCWidget_InventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	return reply;
}

void UCWidget_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CLog::Log("Overlap");
	if (OnSlotHoverd.IsBound())
		OnSlotHoverd.Broadcast(Index);

}
void UCWidget_InventorySlot::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushFromTexture(InIcon);
}

//void UCWidget_InventorySlot::OnClicked()
//{
//	if (OnSlotClicked.IsBound())
//		OnSlotClicked.Broadcast(Index);
//}
//
//void UCWidget_InventorySlot::OnHoverd()
//{
//	if (OnSlotHoverd.IsBound())
//		OnSlotHoverd.Broadcast(Index);
//}
//
//void UCWidget_InventorySlot::OnPressed()
//{
//	
//}
//
//void UCWidget_InventorySlot::OnReleased()
//{
//	if (OnSlotReleased.IsBound())
//		OnSlotReleased.Broadcast(Index);
//}
//
//void UCWidget_InventorySlot::OnUnhovered()
//{
//	if (OnSlotUnhovered.IsBound())
//		OnSlotUnhovered.Broadcast(Index);
//}