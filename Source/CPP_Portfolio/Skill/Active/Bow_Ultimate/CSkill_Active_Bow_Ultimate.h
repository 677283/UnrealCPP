#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_Bow_Ultimate.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_Bow_Ultimate : public UCSkill_Active
{
	GENERATED_BODY()
public:
	UCSkill_Active_Bow_Ultimate();

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACBow_Ultimate_Dragon> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Particle;
public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

};
