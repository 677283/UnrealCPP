#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_SkillTree.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
};
