#pragma once

#include "CoreMinimal.h"
#include "Skill/Passive/CSkill_Passive.h"
#include "CSkill_Passive_Rope.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Passive_Rope : public UCSkill_Passive
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "ºöÀ¸·Î"))
		class UParticleSystem* RopeParticle;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACRope> RopeClass;

public:
	UCSkill_Passive_Rope();
public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	class ACRope* Rope;

};
