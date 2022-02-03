#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItemStructures.generated.h"
//enum HitType
//{
//	Basic, Normal, Fly, PowerLaunch
//};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Equip, Consumable, ETC, Max,
};

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon, Armor, Max,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Dual, Bow, Max,
};

USTRUCT(BlueprintType)
struct FCustomDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		FVector LuanchDirect;
	UPROPERTY(EditDefaultsOnly)
		float LuanchPower;
	//UPROPERTY(EditDefaultsOnly)
	//	class UAnimMontage* HitMontage;
	UPROPERTY(EditDefaultsOnly)
		float PlayRatio;
	UPROPERTY(EditDefaultsOnly)
		int32 AttackLevel;
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

UCLASS()
class CPP_PORTFOLIO_API UCItemStructures : public UObject
{
	GENERATED_BODY()
	
};
