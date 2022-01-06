#pragma once

#include "CoreMinimal.h"
#include "Widget/CWidget_Slot.h"
#include "CWidget_Slot_QuickSlot.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Slot_QuickSlot : public UCWidget_Slot
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	class UMaterialInstanceDynamic* Mat;
};
