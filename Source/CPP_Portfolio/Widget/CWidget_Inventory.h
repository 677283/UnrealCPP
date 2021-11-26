#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Inventory.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetSlot(class UCItemAsset* InItem);
};
