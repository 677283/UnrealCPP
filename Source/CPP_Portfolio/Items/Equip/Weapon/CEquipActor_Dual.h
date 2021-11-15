#pragma once

#include "CoreMinimal.h"
#include "Items/Equip/Weapon/CEquipActor.h"
#include "CEquipActor_Dual.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACEquipActor_Dual : public ACEquipActor
{
	GENERATED_BODY()
public:
	ACEquipActor_Dual();

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACEquipActor> SubActorClass;

protected:
	virtual void BeginPlay() override;

public:
	virtual void AttachTo(FName InSocketName) override;

private:
	class ACEquipActor* SubActor;
};
