#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISlotWidget.generated.h"

UINTERFACE(MinimalAPI)
class UISlotWidget : public UInterface
{
	GENERATED_BODY()
};

class CPP_PORTFOLIO_API IISlotWidget
{
	GENERATED_BODY()

public:
	virtual class UTexture2D* GetIcon() = 0;
	virtual void ActiveSlot() = 0;
};
