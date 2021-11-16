#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "CSkill_Active.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active : public UCSkill
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		float Cooldown;


public:
	UCSkill_Active();

	virtual void BeginPlay(class ACharacter* InOwner) override;

protected:
	class UCStateComponent* State;
};
