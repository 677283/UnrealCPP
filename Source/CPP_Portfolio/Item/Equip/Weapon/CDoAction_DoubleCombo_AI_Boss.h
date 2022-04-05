#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/Weapon/CDoAction_DoubleCombo.h"
#include "CDoAction_DoubleCombo_AI_Boss.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCDoAction_DoubleCombo_AI_Boss : public UCDoAction_DoubleCombo
{
	GENERATED_BODY()
	
public:
	virtual void EndDoAction() override;
	void ResetDoAction();
};
