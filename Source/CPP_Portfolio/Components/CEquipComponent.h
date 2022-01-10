#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnEquip_EquipComponent, class UCItem*, class UCItem*);
DECLARE_DELEGATE_RetVal_OneParam(bool, FOnUnequip_EquipComponent, class UCItem*);
DECLARE_DELEGATE_TwoParams(FOnEquipWidget, FString, class UObject*);

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
	void EquipSubWeapon(class UCEquipItem* InItem);
	void UnequipItem(FString InName);
	FORCEINLINE class UCWeaponItem* GetWeapon() { return Weapon; }
	bool IsHandsOn();

private:
	class ACharacter* OwnerCharacter;
	UPROPERTY()
	class UCWeaponItem* Weapon;
	UPROPERTY()
	class UCWeaponItem* SubWeapon;
	
	class UCWidget_Equip* EquipWidget;

public:
	FOnEquip_EquipComponent OnEquip;
	FOnUnequip_EquipComponent OnUnequip;
	FOnEquipWidget OnEquipWidget;
	//FOnEquipWidget OnUnequipWidget;
};
