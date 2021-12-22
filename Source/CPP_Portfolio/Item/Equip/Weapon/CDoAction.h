#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item/CItemStructures.h"
#include "CDoAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnDoActionBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackerCauser, class ACharacter*, InOtherCharacter, float, InActionDamage, FCustomDamageEvent, InDamageEvent);

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCDoAction : public UObject
{
	GENERATED_BODY()

public:
	UCDoAction();

	virtual void BeginPlay(class ACharacter* InOwner);	

	virtual void DoAction(FKey InKey) {}
	virtual void BeginDoAction() {}
	virtual void EndDoAction() {}

	void SetOwnerCharacter(class ACharacter* InOwner);

	FORCEINLINE void OnCombo() { bComboEnable = true; }
	FORCEINLINE void OffCombo() { bComboEnable = false; }
	FORCEINLINE void InitHands(const bool* InHands) { bHands = InHands; }

public:
	UFUNCTION()
		virtual void OnEquipActorBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
public:
	UFUNCTION()
		void OnEquipActorCollision();

protected:
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
	bool bComboEnable;
	bool bOnCombo;
	const bool* bHands;
	TArray<class ACharacter*> HittedCharacters;

public:
	FOnDoActionBeginOverlap OnDoActionBeginOverlap;

};
