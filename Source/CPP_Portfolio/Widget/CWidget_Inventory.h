#pragma once

#include "CoreMinimal.h"
#include "Widget/CWindowWidget.h"
#include "CWidget_Inventory.generated.h"

DECLARE_DELEGATE_TwoParams(FOnSwapItem, UObject*, UObject*);
DECLARE_DELEGATE_OneParam(FOnUseItem, int32);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Inventory : public UCWindowWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_InventoryDragAndDrop> DragAndDropClass;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetSlotIcon(int32 InIndex, class UTexture2D* InIcon);

private:
	UFUNCTION()
		void OnSlotPressed(int32 InIndex);
	UFUNCTION()
		void OnSlotReleased(int32 InIndex);
	UFUNCTION()
		void OnSlotDoubleClick(int32 InIndex);

	void OnDataCheck(class UCSlotWidget* UpSlot, class UCSlotWidget* DownSlot);
	void InventoryDataCheck(class UCSlotWidget* UpSlot, class UCSlotWidget* DownSlot);
	void EquipDataCheck(class UCSlotWidget* UpSlot, class UCSlotWidget* DownSlot);
	void QuickSlotDataCheck(class UCSlotWidget* UpSlot, class UCSlotWidget* DownSlot);

public:
	void OnAddItem(int32 InIndex, UObject* InItem);

private:
	TArray<class UCSlotWidget*> Slots;
	class UCWidget_InventoryDragAndDrop* DragAndDrop;
	int32 PressedIndex;
	bool bPressed=false;
	bool bHovered = false;

public:
	FOnSwapItem OnSwapItem;
	FOnUseItem OnUseItem;
};
