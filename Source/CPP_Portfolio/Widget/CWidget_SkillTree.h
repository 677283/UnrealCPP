#pragma once

#include "CoreMinimal.h"
#include "Widget/CWindowWidget.h"
#include "CWidget_SkillTree.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree : public UCWindowWidget
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
