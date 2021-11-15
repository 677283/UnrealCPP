#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CEquipment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleHands, FName, InSocketName);

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCEquipment : public UObject
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
	virtual void BeginPlay(class ACharacter* InOwner);

	virtual void Equip();
	virtual void Unequip();
	
	virtual void OnHands();
	virtual void Begin_OnHands();
	virtual void End_OnHands();
	virtual void OffHands();
	virtual void ToggleHands();

	FORCEINLINE const bool* GetHands() { return &bHands; }
public:
	bool bHands;
private:
	class ACharacter* OwnerCharacter;


public:
	FToggleHands OnEquipmentToggleHands;
};
