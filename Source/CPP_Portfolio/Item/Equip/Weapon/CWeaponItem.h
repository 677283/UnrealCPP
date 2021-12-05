#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/CEquipItem.h"
#include "CWeaponItem.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWeaponItem : public UCEquipItem
{
	GENERATED_BODY()
	
public:
	UCWeaponItem();

public:
	void InitializeWeaponItem(class ACEquipActor* InEquipActor, class UCDoAction* InDoAction, class UCEquipment_Weapon* InEquipment, EWeaponType InWeaponType, float InMinDamage, float InMaxDamage);
	virtual void UseItem() override;
	virtual void DestroyItem() override;
private:
	void SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter, float InActionDamage, FCustomDamageEvent InDamageEvent);
public:
	UFUNCTION()
		void OnDoActionBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackerCauser, class ACharacter* InOtherCharacter, float InActionDamage, FCustomDamageEvent InDamageEvent);
public:

	void Do_Action(class ACharacter* InOwner, FKey InKey);
	void BeginDoAction(class ACharacter* InOwner);
	void EndDoAction(class ACharacter* InOwner);

	void OnHands();
	void BeginOnHands();
	void EndOnHands();
	void OffHands();
	void ToggleHands();

	virtual void DropItem(FVector InDropPosition) override;
	virtual void PickUpItem(class ACharacter* InOwner) override;

public:
	FORCEINLINE class ACEquipActor* GetEquipActor() { return EquipActor; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCEquipment_Weapon* GetEquipment() { return Equipment; }
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE bool IsHandsOn() { return *bOnHands; }

private:
	EWeaponType WeaponType;
	class ACEquipActor* EquipActor;
	UPROPERTY()
		class UCDoAction* DoAction;
	UPROPERTY()
		class UCEquipment_Weapon* Equipment;
	const bool* bOnHands;
	class UCEquipComponent* EquipComponent;

private:
	float MinDamage;
	float MaxDamage;

};
