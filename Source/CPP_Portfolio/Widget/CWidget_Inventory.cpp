#include "CWidget_Inventory.h"
#include "Global.h"
#include "Item/CItemAsset.h"
#include "Widget/CWidget_InventorySlot.h"
#include "Widget/CWidget_InventoryDragAndDrop.h"
#include "Widget/CSlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

#include "Widget/CWidget_TitleBar.h"

void UCWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	//Base Setting
	{
		SetVisibility(ESlateVisibility::Hidden);
		bIsFocusable = true;
	}

	//Slot Setting
	{
		TArray<UWidget*> widgets;
		WidgetTree->GetAllWidgets(widgets);

		for (UWidget* widget : widgets)
		{
			UCSlotWidget* slot = Cast<UCSlotWidget>(widget);
			if (!!slot)
			{
				Slots.Add(slot);
				slot->OnDataCheck.BindUObject(this, &UCWidget_Inventory::OnDataCheck);
			}
			/*UCWidget_InventorySlot* slot = Cast<UCWidget_InventorySlot>(widget);
			if (!!slot)
			{
				Slots.Add(slot);
				slot->OnSlotReleased.AddDynamic(this, &UCWidget_Inventory::OnSlotReleased);
				slot->OnSlotPressed.AddDynamic(this, &UCWidget_Inventory::OnSlotPressed);
				slot->OnSlotDoubleClick.AddDynamic(this, &UCWidget_Inventory::OnSlotDoubleClick);

			}*/
		}
	}

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DragAndDrop = CreateWidget<UCWidget_InventoryDragAndDrop, APlayerController>(controller, DragAndDropClass, "DragAndDrop");
	DragAndDrop->AddToViewport(44);
	DragAndDrop->SetVisibility(ESlateVisibility::Hidden);

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

void UCWidget_Inventory::SetSlotIcon(int32 InIndex, UTexture2D* InIcon)
{
	Slots[InIndex]->SetIcon(InIcon);
}

void UCWidget_Inventory::OnSlotPressed(int32 InIndex)
{
	/*CheckNull(Slots[InIndex]->GetIcon());
	{
		DragAndDrop->SetIcon(Slots[InIndex]->GetIcon());
		DragAndDrop->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	bPressed = true;
	PressedIndex = InIndex;*/
}

void UCWidget_Inventory::OnSlotReleased(int32 InIndex)
{
	/*CheckFalse(bPressed);
	CheckTrue(InIndex == PressedIndex);
	
	{
		int32 sizeX, sizeY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
		DragAndDrop->SetPositionInViewport(FVector2D(sizeX, sizeY));
	}

	bPressed = false;

	OnSwapItem.ExecuteIfBound(PressedIndex, InIndex);*/
}

void UCWidget_Inventory::OnSlotDoubleClick(int32 InIndex)
{
	OnUseItem.ExecuteIfBound(InIndex);
}

void UCWidget_Inventory::OnDataCheck(UCSlotWidget* UpSlot, UCSlotWidget* DownSlot)
{
	switch (DownSlot->GetSlotType())
	{
		case ESlotType::Inventory:
			InventoryDataCheck(UpSlot, DownSlot);
			break;
		case ESlotType::Equip:
			EquipDataCheck(UpSlot, DownSlot);
			break;
		case ESlotType::QuickSlot:
			QuickSlotDataCheck(UpSlot, DownSlot);
			break;
	}
}
void UCWidget_Inventory::InventoryDataCheck(UCSlotWidget* UpSlot, UCSlotWidget* DownSlot)
{
	CheckNull(DownSlot->GetData());

	DownSlot->SwapData(UpSlot);
	OnSwapItem.ExecuteIfBound(UpSlot->GetData(), DownSlot->GetData());
}

void UCWidget_Inventory::EquipDataCheck(UCSlotWidget* UpSlot, UCSlotWidget* DownSlot)
{

}

void UCWidget_Inventory::QuickSlotDataCheck(UCSlotWidget* UpSlot, UCSlotWidget* DownSlot)
{

}

void UCWidget_Inventory::OnAddItem(int32 InIndex, UObject* InItem)
{
	CLog::Log("INDEX : " + FString::FromInt(InIndex));
	CheckFalse(Slots.Num() > InIndex);
	Slots[InIndex]->SetData(InItem);
}
