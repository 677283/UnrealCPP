#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "CSkill_Passive.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Passive : public UCSkill
{
	GENERATED_BODY()
	
public:
	UCSkill_Passive();

	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
};
