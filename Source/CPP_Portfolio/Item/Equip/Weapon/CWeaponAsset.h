#pragma once

#include "CoreMinimal.h"
#include "Item/Equip/CEquipAsset.h"
#include "GameFramework/Character.h"
#include "CWeaponAsset.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Dual, Max,
};

USTRUCT(BlueprintType)
struct FCustomDamageEvent : public FDamageEvent
{
	GENERATED_BODY()

public:
	FVector LuanchDirect;
	float LuanchPower;
	class UAnimMontage* HitMontage;

	void PlayHitMontage(class ACharacter* InCharacter)
	{
		if (!HitMontage)
		{
			//TODO ±âº» ¸ùÅ¸Áê ¼³Á¤
			return;
		}
		InCharacter->PlayAnimMontage(HitMontage);
	}
};


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
	FORCEINLINE class ACEquipActor* GetEquipActor() { return EquipActor; }
	FORCEINLINE class UCDoAction* GetDoAction() { return DoAction; }
	FORCEINLINE class UCEquipment_Weapon* GetEquipment() { return Equipment; }
	FORCEINLINE EWeaponType GetWeaponType() { return WeaponType; }
	FORCEINLINE bool IsHandsOn() { return *bOnHands; }
	virtual void BeginPlay(class ACharacter* InOwner) override;

private:
	void SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter, float InActionDamage);

public:
	UFUNCTION()
		void OnDoActionBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackerCauser, class ACharacter* InOtherCharacter, float InActionDamage);
public:

	void Do_Action(class ACharacter* InOwner, FKey InKey);
	void BeginDoAction(class ACharacter* InOwner);
	void EndDoAction(class ACharacter* InOwner);
	
	void OnHands(class ACharacter* InOwner);
	void BeginOnHands(class ACharacter* InOwner);
	void EndOnHands(class ACharacter* InOwner);

	virtual void DropItem(FVector InDropPosition) override;
	virtual void PickUpItem(class ACharacter* InOwner) override;

private:
	class ACEquipActor* EquipActor;
	class UCDoAction* DoAction;
	class UCEquipment_Weapon* Equipment;
	const bool* bOnHands;
};