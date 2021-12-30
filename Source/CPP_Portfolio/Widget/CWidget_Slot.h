#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Slot.generated.h"

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	Inventory, Equip, SkillTree, QuickSlot, Max,
};

DECLARE_DELEGATE_TwoParams(FSlotOnDataCheck, UCWidget_Slot*, UCWidget_Slot*);
DECLARE_DELEGATE_OneParam(FOnSlotDoubleClick, UCWidget_Slot*);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Slot : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UObject>> SlotDataClasses;
	
	UPROPERTY(EditAnywhere, NoClear)
		TSubclassOf<class UCWidget_DragAndDrop> DragAndDropClass;

	UPROPERTY(EditAnywhere)
		FString IconWidgetName;

	UPROPERTY(EditAnywhere, NoClear)
		ESlotType Type;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetData(UObject* InData);
	void SwapData(UCWidget_Slot* InSlot);
	void SetIcon(class UTexture2D* InIcon);
	FORCEINLINE UObject* GetData() { return SlotData; }
	FORCEINLINE ESlotType GetSlotType() { return Type; }

private:
	static UCWidget_Slot* SelectSlot;
	static class UCWidget_DragAndDrop* DragAndDrop;

private:
	UObject* SlotData;
	class UImage* IconWidget;

public:
	FSlotOnDataCheck OnDataCheck;
	FOnSlotDoubleClick OnSlotDoubleClick;

};
