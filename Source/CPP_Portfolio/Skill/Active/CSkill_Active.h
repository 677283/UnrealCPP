#pragma once

#include "CoreMinimal.h"
#include "Skill/CSkill.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "CSkill_Active.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active : public UCSkill
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		float Cooldown = 0;

	UPROPERTY(EditDefaultsOnly)
		TArray<EWeaponType> NeedWeaponTypes;

	UPROPERTY(EditDefaultsOnly)
		bool bNeedWeapon;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly)
		float PlayRatio = 1;

public:
	UCSkill_Active();

	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;

protected:
	bool WeaponCheck();

protected:
	class UCStateComponent* State;
	class UCEquipComponent* Equip;
};
