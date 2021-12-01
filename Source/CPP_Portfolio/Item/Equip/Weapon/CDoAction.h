#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDoAction.generated.h"


USTRUCT(BlueprintType)
struct FCustomDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		FVector LuanchDirect;
	UPROPERTY(EditDefaultsOnly)
		float LuanchPower;
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* HitMontage;
	UPROPERTY(EditDefaultsOnly)
		float PlayRatio;
};

USTRUCT(BlueprintType)
struct FDoActionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montage;
	UPROPERTY(EditDefaultsOnly)
		float PlayRatio = 1;
	UPROPERTY(EditDefaultsOnly)
		float AddDamage;
	UPROPERTY(EditDefaultsOnly)
		FCustomDamageEvent DamageEvent;
};

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

	FORCEINLINE void OnCombo() { bComboEnable = true; }
	FORCEINLINE void OffCombo() { bComboEnable = false; }
	FORCEINLINE void InitHands(const bool* InHands) { bHands = InHands; }
	void SetOwnerCharacter(class ACharacter* InOwner);

public:
	UFUNCTION()
		virtual void OnEquipActorBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}
public:
	UFUNCTION()
		void OnEquipActorCollision();

protected:
	class ACharacter* OwnerCharacter;
	class UCItemAsset* ItemAsset;
	class UCStateComponent* State;
	bool bComboEnable;
	bool bOnCombo;
	const bool* bHands;
	TArray<class ACharacter*> HittedCharacters;

public:
	FOnDoActionBeginOverlap OnDoActionBeginOverlap;

};
