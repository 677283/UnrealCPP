#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/CEquipment.h"
#include "CEquipment_Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleHands, FName, InSocketName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipAndUnequip);

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCEquipment_Weapon : public UCEquipment
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		float EquipPlayRatio = 1;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		FName EquipSocket;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		FName UnequipSocket;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;

	virtual void Equip() override;
	virtual void Unequip() override;
	
	virtual void OnHands();
	virtual void Begin_OnHands();
	virtual void End_OnHands();
	virtual void OffHands();
	virtual void ToggleHands();

	FORCEINLINE const bool* GetHands() { return &bHands; }
private:
	bool bHands;

public:
	FToggleHands OnEquipmentToggleHands;
	FOnEquipAndUnequip OnEquip;
	FOnEquipAndUnequip OnUnequip;
};
