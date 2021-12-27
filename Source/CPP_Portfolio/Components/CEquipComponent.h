#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CEquipComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipComponentEquipAndUnequip, class UCItem*, InEquipItem, class UCItem*, InUnequipItem);
DECLARE_DELEGATE_TwoParams(FEquipOnUpdateIcon, FString, class UTexture2D*);

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
	void UnequipItem(FString InName);
	FORCEINLINE class UCWeaponItem* GetWeapon() { return Weapon; }
	bool IsHandsOn();

private:
	class ACharacter* OwnerCharacter;
	UPROPERTY()
	class UCWeaponItem* Weapon;
	class UCWidget_Equip* EquipWidget;

public:
	FOnEquipComponentEquipAndUnequip OnEquip;
	FOnEquipComponentEquipAndUnequip OnUnequip;
	FEquipOnUpdateIcon OnUpdateIcon;
};
