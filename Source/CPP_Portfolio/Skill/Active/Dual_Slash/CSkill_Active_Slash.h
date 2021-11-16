#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_Slash.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_Slash : public UCSkill_Active
{
	GENERATED_BODY()
public:
	UCSkill_Active_Slash();

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACSlashProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
		float PlayRatio = 1;
public:
	virtual void BeginPlay(class ACharacter* InOwner);
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	class UAnimMontage* Montage;
};
