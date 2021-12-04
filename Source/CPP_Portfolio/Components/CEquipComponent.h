#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipComponentEquipAndUnequip, class UCItem*, InItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCEquipComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	void EquipItem(class UCEquipItem* InItem);
	//void UnequipImte()
	FORCEINLINE class UCWeaponItem* GetWeapon() { return Weapon; }
	bool IsHandsOn();

private:
	UPROPERTY()
		class UCWeaponItem* Weapon;

public:
	FOnEquipComponentEquipAndUnequip OnEquip;
	FOnEquipComponentEquipAndUnequip OnUnequip;
};
