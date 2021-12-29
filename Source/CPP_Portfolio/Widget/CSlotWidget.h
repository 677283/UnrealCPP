#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSlotWidget.generated.h"

UENUM(BlueprintType)
enum class ESlotType : uint8
{
	Inventory, Equip, SkillTree, QuickSlot, Max,
};

DECLARE_DELEGATE_TwoParams(FSlotOnDataCheck, UCSlotWidget*, UCSlotWidget*);

UCLASS()
class CPP_PORTFOLIO_API UCSlotWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<UObject>> SlotDataClasses;
	
	UPROPERTY(EditAnywhere)
		FString IconWidgetName;

	UPROPERTY(EditAnywhere, NoClear)
		ESlotType Type;

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetData(UObject* InData);
	void SwapData(UCSlotWidget* InSlot);
	void SetIcon(class UTexture2D* InIcon);
	FORCEINLINE UObject* GetData() { return SlotData; }
	FORCEINLINE ESlotType GetSlotType() { return Type; }

private:
	static UCSlotWidget* SelectSlot;

private:
	UObject* SlotData;
	class UImage* IconWidget;

public:
	FSlotOnDataCheck OnDataCheck;

};
