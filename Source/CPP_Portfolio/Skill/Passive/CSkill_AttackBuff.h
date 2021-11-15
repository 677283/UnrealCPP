#pragma once

#include "CoreMinimal.h"
#include "Skill/Passive/CSkill_Passive.h"
#include "CSkill_AttackBuff.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_AttackBuff : public UCSkill_Passive
{
	GENERATED_BODY()
	
public:
	virtual void DoSkill() override;

};
