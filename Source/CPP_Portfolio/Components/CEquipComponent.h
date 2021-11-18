#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	class UCEquipAsset* EquipItem(class UCEquipAsset* InItem);
	FORCEINLINE class UCWeaponAsset* GetWeapon() { return Weapon; }
	FORCEINLINE bool IsHandsOn() { return *bOnHands; }

private:
	class UCWeaponAsset* Weapon;
	const bool* bOnHands;
};
