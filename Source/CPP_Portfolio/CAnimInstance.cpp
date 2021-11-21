#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	Equip = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	
	UCWeaponAsset* weapon = Equip->GetWeapon();
	CheckNull(weapon);
	*(weapon->GetEquipment()->GetHands()) ? WeaponType = weapon->GetWeaponType() : WeaponType = EWeaponType::Max;
	
	//Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
}