#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/CEquipAsset.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "Item/CItemStructures.h"
#include "GameFramework/Character.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWeaponAsset : public UCEquipAsset
{
	GENERATED_BODY()
	
public:
	UCWeaponAsset();

private:
	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		TSubclassOf<class ACEquipActor> EquipActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		TSubclassOf<class UCEquipment_Weapon> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		float MinDamage = 0.0;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
		float MaxDamage = 0.0;

	UPROPERTY(EditDefaultsOnly)
		EWeaponType WeaponType;

public:

	virtual class UCItem* CreateItem(class ACharacter* InOwner, class UCItem* InItem) override;
};