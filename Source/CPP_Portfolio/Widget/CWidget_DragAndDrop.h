#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_DragAndDrop.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_DragAndDrop : public UUserWidget
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
