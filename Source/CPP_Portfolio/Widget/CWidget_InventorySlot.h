#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "CWidget_InventorySlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotHoverd, int32, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotPressed, int32, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotReleased, int32, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotUnhovered, int32, InIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotDoubleClick, int32, InIndex);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
public:
	void SetIcon(class UTexture2D* InIcon);

public:
	FOnSlotHoverd OnSlotHoverd;
	FOnSlotPressed OnSlotPressed;
	FOnSlotReleased OnSlotReleased;
	FOnSlotUnhovered OnSlotUnhovered;
	FOnSlotDoubleClick OnSlotDoubleClick;
	int32 Index;

private:
	class UImage* Icon;
};
