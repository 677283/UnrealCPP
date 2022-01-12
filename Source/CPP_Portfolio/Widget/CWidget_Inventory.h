#pragma once

#include "CoreMinimal.h"
#include "Widget/CWidget_Window.h"
#include "CWidget_Inventory.generated.h"

DECLARE_DELEGATE_TwoParams(FOnSwapItem, int32, int32);
DECLARE_DELEGATE_OneParam(FOnUseItem, class UCItem*);
DECLARE_DELEGATE_OneParam(FOnUnequip_InvenWidget, FString);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Inventory : public UCWidget_Window
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_InventoryDragAndDrop> DragAndDropClass;

protected:
	virtual void NativeConstruct() override;

private:
	void OnSlotDoubleClick(class UCWidget_Slot* InSlot);

	void OnDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);
	void InventoryDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);
	void EquipDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);
	void QuickSlotDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);

public:
	void OnAddItem(int32 InIndex, UObject* InItem);
	void OnSlotUpdate(int32 InIndex, class UCItem* InItem);

private:
	TArray<class UCWidget_Slot*> Slots;
	class UCWidget_InventoryDragAndDrop* DragAndDrop;

public:
	FOnSwapItem OnSwapItem;
	FOnUseItem OnUseItem;
	FOnUnequip_InvenWidget OnUnequip_InvenWidget;
};
