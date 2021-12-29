#pragma once

#include "CoreMinimal.h"
#include "Widget/CWidget_Window.h"
#include "CWidget_SkillTree.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree : public UCWidget_Window
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditAnywhere, NoClear)
		class UWidget* ActiveTab;

private:
	void OnToggleTab(class UWidget* InTab);

};
