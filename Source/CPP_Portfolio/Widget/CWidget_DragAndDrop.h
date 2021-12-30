#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_DragAndDrop.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_DragAndDrop : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, NoClear)
		FString IconSlotName;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetIcon(class UTexture2D* InIcon);
	void SetActive(bool InActive);

private:
	class UImage* Icon;
	bool bIsActive;
};
