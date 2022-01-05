#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_TitleBar_Button.generated.h"

DECLARE_DELEGATE(FOnMouseDwon_TitleBarButton);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_TitleBar_Button : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	FOnMouseDwon_TitleBarButton OnMouseDwon;
};
