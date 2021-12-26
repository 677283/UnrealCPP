#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Equip_Slot.generated.h"

DECLARE_DELEGATE_OneParam(FOnEquipSlot, FString);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Equip_Slot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
public:
	void SetIcon(class UTexture2D* InIcon);

private:
	class UImage* Icon;

public:
	FOnEquipSlot OnSlotMouseButtonDown;
	FOnEquipSlot OnSlotMouseButtonUp;
	FOnEquipSlot OnSlotMouseButtonDouble;

};
