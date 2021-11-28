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
	
	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);
	
	for (UWidget* widget : widgets)
	{
		UCWidget_InventorySlot* slot = Cast<UCWidget_InventorySlot>(widget);
		if (!!slot)
		{
			Slots.Add(slot);
			slot->OnSlotHoverd.AddDynamic(this, &UCWidget_Inventory::OnSlotHoverd);
			slot->OnSlotReleased.AddDynamic(this, &UCWidget_Inventory::OnSlotReleased);
			slot->OnSlotPressed.AddDynamic(this, &UCWidget_Inventory::OnSlotPressed);
			slot->OnSlotUnhovered.AddDynamic(this, &UCWidget_Inventory::OnSlotUnhoverd);
			slot->OnSlotDoubleClick.AddDynamic(this, &UCWidget_Inventory::OnSlotDoubleClick);
		}
	}

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	DragAndDrop = CreateWidget<UCWidget_DragAndDrop, APlayerController>(controller, DragAndDropClass, "DragAndDrop");
	DragAndDrop->AddToViewport(1);

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Inventory = CHelpers::GetComponent<UCInventoryComponent>(player);
	Inventory->OnAddItem.AddDynamic(this, &UCWidget_Inventory::OnAddItem);
}

void UCWidget_Inventory::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	float x, y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
	FVector2D pos(x, y);
	FVector2D size = DragAndDrop->GetDesiredSize();
	pos.X -= size.X / 2;
	pos.Y -= size.Y / 2;
	//DragAndDrop->SetPositionInViewport(pos);
}

FReply UCWidget_Inventory::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CLog::Log("Inven Release");
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	CheckFalseResult(bPressed, reply);

	bPressed = false;

	return reply;
}

FReply UCWidget_Inventory::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	CLog::Log("input");
	FReply reply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == FKey("I"))
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->SetShowMouseCursor(false);
		controller->SetInputMode(FInputModeGameOnly());

		this->SetVisibility(ESlateVisibility::Hidden);
	}

	return reply;
}

void UCWidget_Inventory::UpdateSlot()
{
	for (int32 i = 0; i < Slots.Num(); i++)
	{
		Slots[i]->SetIcon(Inventory->GetIcon(i));
	}
}

void UCWidget_Inventory::OnSlotHoverd(int32 InIndex)
{
	HoveredIndex = InIndex;
}

void UCWidget_Inventory::OnSlotPressed(int32 InIndex)
{
	CheckFalse(Inventory->CheckSlot(InIndex));

	bPressed = true;
	PressedIndex = InIndex;
}

void UCWidget_Inventory::OnSlotReleased(int32 InIndex)
{
	CheckFalse(bPressed);

	bPressed = false;
	Inventory->SwapItem(PressedIndex, InIndex);
	UpdateSlot();
}

void UCWidget_Inventory::OnSlotUnhoverd(int32 InIndex)
{
	HoveredIndex = -1;
}

void UCWidget_Inventory::OnSlotDoubleClick(int32 InIndex)
{

}

void UCWidget_Inventory::OnAddItem()
{
	UpdateSlot();
}