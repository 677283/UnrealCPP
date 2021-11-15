#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDoAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDoActionBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackerCauser, class ACharacter*, InOtherCharacter, float, InActionDamage);

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
		FVector LuanchDirection;
};

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

private:
	virtual void OnEquipActorBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter) {}

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
