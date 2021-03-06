#include "CAnimInstance.h"
#include "Global.h"
//#include "GameFramework/Character.h"
#include "Character/CCharacter.h"
#include "GameFramework/NavMovementComponent.h"
#include "Horse/CHorse.h"
#include "Components/CEquipComponent.h"
#include "Components/CRidingComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACCharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	Equip = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
	Riding = CHelpers::GetComponent<UCRidingComponent>(OwnerCharacter);
	Movement = CHelpers::GetComponent<UNavMovementComponent>(OwnerCharacter);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);
	bRiding = Riding->IsRiding();
	bJumping = Movement->IsFalling();
	bSecondJump = OwnerCharacter->IsSecondJump();

	if (bRiding)
	{
		Speed = Riding->GetRidingHorse()->GetVelocity().Size2D();
		Direction = OwnerCharacter->GetActorRotation().Yaw - LastRotate.Yaw;
		float abs = UKismetMathLibrary::Abs(Direction);
		if (abs > 100)
			Direction *= -1;
		LastRotate = OwnerCharacter->GetActorRotation();
	}
	else
	{
		Speed = OwnerCharacter->GetVelocity().Size2D();
		Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	}

	UCWeaponItem* weapon = Equip->GetWeapon();
	if (!!weapon)
		weapon->IsHandsOn() ? WeaponType = weapon->GetWeaponType() : WeaponType = EWeaponType::Max;
	else
		WeaponType = EWeaponType::Max;
}