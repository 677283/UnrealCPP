#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_Subjugate.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_Subjugate : public UCSkill_Active
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Particle;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACSubjugate_Actor> Subgate_Projectile;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	void Pattern_0();
	void Pattern_1();
};
