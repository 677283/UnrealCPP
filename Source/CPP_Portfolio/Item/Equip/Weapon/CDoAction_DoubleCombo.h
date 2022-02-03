#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "CDoAction_DoubleCombo.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCDoAction_DoubleCombo : public UCDoAction
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		TMap<FString, FDoActionData> ComboList;
public:
	virtual void DoAction(FKey InKey) override;
	virtual void BeginDoAction() override;
	virtual void EndDoAction() override;
	virtual void ResetDoAction() override;

public:
	virtual void OnEquipActorBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) override;
		
private:
	FString ComboKey;
	FKey LastKey;
};
