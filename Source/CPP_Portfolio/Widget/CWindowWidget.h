#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWindowWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnZUpdate, class UWidget*);

UCLASS()
class CPP_PORTFOLIO_API UCWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

private:
	void UpdateZOrder();

public:
	FOnZUpdate OnZUpdate;

};
