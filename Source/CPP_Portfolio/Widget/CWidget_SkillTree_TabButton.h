#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_SkillTree_TabButton.generated.h"

DECLARE_DELEGATE_OneParam(FOnSkillTreeToggleTab, class UWidget*);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree_TabButton : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		class UWidget* Tab;

protected:
	virtual void NativeConstruct();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

public:
	FORCEINLINE class UWidget* GetTab() { return Tab; }
public:
	FOnSkillTreeToggleTab OnToggleTab;
};
