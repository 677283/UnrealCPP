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
	Dual, Bow, ETC, Max,
};

USTRUCT(BlueprintType)
struct FCustomDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		FRotator LaunchDirectAngle = FRotator(0, 180, 0);
	UPROPERTY(EditDefaultsOnly)
		float LaunchPower = 100;
	UPROPERTY(EditDefaultsOnly)
		float PlayRatio = 1.0f;
	UPROPERTY(EditDefaultsOnly)
		int32 AttackLevel = 0;
	/*
		AttackLevel
		1 : Basic Attack
		2 : Strong Attack
		3 : Airbone Attack
	*/
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
