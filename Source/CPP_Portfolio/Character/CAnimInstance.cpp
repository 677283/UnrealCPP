#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Horse/CHorse.h"
#include "Components/CEquipComponent.h"
#include "Components/CRidingComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	Equip = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
	Riding = CHelpers::GetComponent<UCRidingComponent>(OwnerCharacter);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());

	UCWeaponItem* weapon = Equip->GetWeapon();
	if (!!weapon)
		weapon->IsHandsOn() ? WeaponType = weapon->GetWeaponType() : WeaponType = EWeaponType::Max;
	bRiding = Riding->IsRiding();

	//Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
}