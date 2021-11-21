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
		TSubclassOf<class ACBoomerang_Throw> BoomerangClass;

public:
	virtual void BeginPlay(class ACharacter* InOwner);
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	void OnBoomerangBeginOverlap(class AActor* OtherActor);

private:
	class ACEquipActor_Dual* Weapon;
	TArray<class AActor*> Boomerangs;
};
