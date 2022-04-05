#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_SpawnClone.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_SpawnClone : public UCSkill_Active
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AActor> CloneClass;

	UPROPERTY(EditDefaultsOnly)
		float SpawnRange = 200;

	UPROPERTY(EditDefaultsOnly)
		int32 SpawnCount = 1;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override; 

private:
	void SpawnCloneTimer();

private:
	FTimerHandle SpawnCloneTimerHandle;
	int32 SpawnCountCheck;
};
