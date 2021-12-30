#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_TitleBar.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_TitleBar : public UUserWidget
{
	GENERATED_BODY()
			
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	//virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
public:
	void SetMove(class UUserWidget* InWidget);

private:
	void OnMouseDown();

private:
	class UUserWidget* MoveWidget;
	class UCanvasPanelSlot* MoveSlot;
	bool Flag;
	FVector2D Offset;
	FVector2D Offset2;
};
