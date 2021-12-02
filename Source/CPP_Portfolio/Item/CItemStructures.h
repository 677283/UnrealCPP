#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItemStructures.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Equip, Consumable, ETC, Max,
};

UCLASS()
class CPP_PORTFOLIO_API UCItemStructures : public UObject
{
	GENERATED_BODY()
	
};
