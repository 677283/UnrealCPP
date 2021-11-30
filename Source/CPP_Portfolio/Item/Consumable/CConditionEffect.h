#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CConditionEffect.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCConditionEffect : public UObject
{
	GENERATED_BODY()
	
public:
	void AddCondition(class ACharacter* InOwner, float InValue) {};
};
