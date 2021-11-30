#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SlateWrapperTypes.h"
#include "CWidget_InventorySlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseDelegate, int32, InIndex);

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
	FOnMouseDelegate OnSlotHoverd;
	FOnMouseDelegate OnSlotPressed;
	FOnMouseDelegate OnSlotReleased;
	FOnMouseDelegate OnSlotUnhovered;
	FOnMouseDelegate OnSlotDoubleClick;
	int32 Index;

private:
	class UImage* Icon;
};
