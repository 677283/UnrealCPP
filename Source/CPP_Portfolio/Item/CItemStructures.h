#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItemStructures.generated.h"

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
	Dual, Max,
};


UCLASS()
class CPP_PORTFOLIO_API UCItemStructures : public UObject
{
	GENERATED_BODY()
	
};
