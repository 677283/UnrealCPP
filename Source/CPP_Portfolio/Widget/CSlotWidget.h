#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSlotWidget.generated.h"

DECLARE_DELEGATE_OneParam(FSlotOnSetData, UObject*);
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


protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetData(UObject* InData);
	void SwapData(UCSlotWidget* InSlot);
	void SetIcon(class UTexture2D* InIcon);
	FORCEINLINE UObject* GetData() { return SlotData; }

private:
	static UCSlotWidget* SelectData;

private:
	UObject* SlotData;
	class UImage* IconWidget;

public:
	FSlotOnDataCheck OnDataCheck;
	FSlotOnSetData OnSetData;
};
