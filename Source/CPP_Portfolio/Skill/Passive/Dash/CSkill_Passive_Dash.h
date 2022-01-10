#pragma once

#include "CoreMinimal.h"
#include "Skill/Passive/CSkill_Passive.h"
#include "CSkill_Passive_Dash.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Passive_Dash : public UCSkill_Passive
{
	GENERATED_BODY()

	DECLARE_EVENT(UCSkill_Passive_Dash, FOnEffect);

private:
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* DashMontage;

	UPROPERTY(EditDefaultsOnly)
		class UFXSystemAsset* DashEffect;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	void PlayEffect_Particle();
	void PlayEffect_Niagara();

private:
	class UCStateComponent* State;
	class UParticleSystem* ParticleDash;
	class UNiagaraSystem* NiagaraDash;
	bool bDash=false;

private:
	FOnEffect OnEffect;
};
