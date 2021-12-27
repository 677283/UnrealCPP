#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_InventoryDragAndDrop.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_InventoryDragAndDrop : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void SetIcon(class UTexture2D* InIcon);

private:
	class UImage* Icon;
	class UUserWidget* Wid;
};
