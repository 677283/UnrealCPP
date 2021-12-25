#include "CWidget_Inventory.h"
#include "Global.h"
#include "Item/CItemAsset.h"
#include "Widget/CWidget_InventorySlot.h"
#include "Widget/CWidget_DragAndDrop.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Components/Image.h"

void UCWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();
	
	bIsFocusable = true;

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);
	
	for (UWidget* widget : widgets)
	{
		UCWidget_InventorySlot* slot = Cast<UCWidget_InventorySlot>(widget);
		if (!!slot)
		{
			Slots.Add(slot);
			slot->OnSlotReleased.AddDynamic(this, &UCWidget_Inventory::OnSlotReleased);
			slot->OnSlotPressed.AddDynamic(this, &UCWidget_Inventory::OnSlotPressed);
			slot->OnSlotDoubleClick.AddDynamic(this, &UCWidget_Inventory::OnSlotDoubleClick);
		}
	}

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DragAndDrop = CreateWidget<UCWidget_DragAndDrop, APlayerController>(controller, DragAndDropClass, "DragAndDrop");
	DragAndDrop->AddToViewport(1);
	
	int32 sizeX, sizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
	DragAndDrop->SetPositionInViewport(FVector2D(sizeX, sizeY));

}

void UCWidget_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CheckFalse(bPressed);

	float x, y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
	FVector2D pos(x, y);
	FVector2D size = DragAndDrop->GetCachedGeometry().GetDrawSize();
	
	
	pos.X -= size.X / 2.0f;
	pos.Y -= size.Y / 2.0f;
	DragAndDrop->SetPositionInViewport(pos);
}

FReply UCWidget_Inventory::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	CheckFalseResult(bPressed, reply);
	{
		int32 sizeX, sizeY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
		DragAndDrop->SetPositionInViewport(FVector2D(sizeX, sizeY));
	}
	bPressed = false;

	return reply;
}

void UCWidget_Inventory::SetSlotIcon(int32 InIndex, class UTexture2D* InIcon)
{
	Slots[InIndex]->SetIcon(InIcon);
}

void UCWidget_Inventory::OnSlotPressed(int32 InIndex)
{
	CheckNull(Slots[InIndex]->GetIcon());
	{
		DragAndDrop->SetIcon(Slots[InIndex]->GetIcon());
	}
	bPressed = true;
	PressedIndex = InIndex;
}

void UCWidget_Inventory::OnSlotReleased(int32 InIndex)
{
	CheckFalse(bPressed);
	CheckTrue(InIndex == PressedIndex);
	
	{
		int32 sizeX, sizeY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
		DragAndDrop->SetPositionInViewport(FVector2D(sizeX, sizeY));
	}

	bPressed = false;

	OnSwapItem.ExecuteIfBound(PressedIndex, InIndex);
}

void UCWidget_Inventory::OnSlotDoubleClick(int32 InIndex)
{
	OnUseItem.ExecuteIfBound(InIndex);
}
