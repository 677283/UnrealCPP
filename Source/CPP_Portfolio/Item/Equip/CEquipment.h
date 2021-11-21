#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipment.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCEquipment : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay(class ACharacter* InOwner);

	virtual void Equip() {}
	virtual void Unequip() {}

protected:
	class ACharacter* OwnerCharacter;
	class UCStateComponent* State;
};
