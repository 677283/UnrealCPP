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

public:
	virtual void SetIcon(class UTexture2D* InIcon) override;

private:
	class UMaterialInstanceDynamic* Mat;
	class UTexture* BaseTexture;
};
