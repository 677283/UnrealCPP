#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_Throw.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_Throw : public UCSkill_Active
{
	GENERATED_BODY()
	
public:
	UCSkill_Active_Throw();

private:
	UPROPERTY(EditDefaultsOnly)
		float ThrowSpeed;

public:
	virtual void BeginPlay(class ACharacter* InOwner);
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

};
