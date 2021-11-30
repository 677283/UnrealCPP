#pragma once

#include "CoreMinimal.h"
#include "Item/CItemAsset.h"
#include "CConsumableAsset.generated.h"

UENUM(BlueprintType)
enum class EConditionType : uint8
{
	Healing, ChargeEnergy, AmorUp, Max
};

USTRUCT(BlueprintType)
struct FCondition
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		EConditionType Type;
	UPROPERTY(EditDefaultsOnly)
		float Value;
};

USTRUCT(BlueprintType)
struct FSpecialCondition
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCConditionEffect> Condition;
	UPROPERTY(EditDefaultsOnly)
		float Value;
};


UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCConsumableAsset : public UCItemAsset
{
	GENERATED_BODY()
public:
	UCConsumableAsset();

private:
	UPROPERTY(EditDefaultsOnly)
		TArray<FCondition> Conditions;

	UPROPERTY(EditDefaultsOnly)
		TArray<FSpecialCondition> SpecialConditionClasses;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;

	virtual void UseItem() override;

private:
	void Healing(float InValue);
	void ChargeEnergy(float InValue);

private:
	TArray<class UCConditionEffect*> SpecialConditions;
	class UCStatusComponent* Status;
};
