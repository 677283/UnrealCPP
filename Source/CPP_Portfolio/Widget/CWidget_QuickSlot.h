#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_QuickSlot.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};
