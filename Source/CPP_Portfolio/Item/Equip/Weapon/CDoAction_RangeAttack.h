#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "CDoAction_RangeAttack.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCDoAction_RangeAttack : public UCDoAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACProjectileActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* ShotMontage;

	UPROPERTY(EditDefaultsOnly)
		float ShotDelay = 1.0f;

public:
	virtual void DoAction(FKey InKey) override;
	virtual void BeginDoAction() override;
	virtual void EndDoAction() override;
	
private:
	void CountDelay();

private:
	float StackDelay = 0;
	bool bCanShot = true;
	FTimerHandle TimerHandle;
};
