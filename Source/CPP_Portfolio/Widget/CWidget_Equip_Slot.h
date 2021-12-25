#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Equip_Slot.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Equip_Slot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetIcon(class UTexture2D* InIcon);

private:
	class UImage* Icon;

};
