#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Inventory.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_DragAndDrop> DragAndDropClass;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void UpdateSlot();

private:
	UFUNCTION()
		void OnSlotHoverd(int32 InIndex);
	UFUNCTION()
		void OnSlotPressed(int32 InIndex);
	UFUNCTION()
		void OnSlotReleased(int32 InIndex);
	UFUNCTION()
		void OnSlotUnhoverd(int32 InIndex);
	UFUNCTION()
		void OnSlotDoubleClick(int32 InIndex);
	UFUNCTION()
		void OnInventoryUpdate();

private:
	TArray<class UCWidget_InventorySlot*> Slots;
	class UCWidget_DragAndDrop* DragAndDrop;
	int32 HoveredIndex;
	int32 PressedIndex;
	bool bPressed=false;
	bool bHovered = false;
	class UCInventoryComponent* Inventory;

};
