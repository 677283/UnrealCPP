#include "CWeaponItem.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "Item/Equip/Weapon/CDoAction_DoubleCombo.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponItem.h"

UCWeaponItem::UCWeaponItem()
{

}

void UCWeaponItem::InitializeWeaponItem(class ACEquipActor* InEquipActor, class UCDoAction* InDoAction, class UCEquipment_Weapon* InEquipment, EWeaponType InWeaponType, float InMinDamage, float InMaxDamage)
{
	EquipActor = InEquipActor;
	DoAction = InDoAction;
	Equipment = InEquipment;
	WeaponType = InWeaponType;
	MinDamage = InMinDamage;
	MaxDamage = InMaxDamage;

	bOnHands = Equipment->GetHands();
}

void UCWeaponItem::UseItem()
{
	Super::UseItem();

	EquipComponent = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
	CheckNull(EquipComponent);
	Equipment->Equip();
	EquipComponent->EquipItem(this);
}

void UCWeaponItem::DestroyItem()
{
	//TODO DoAction,Equipment,EquipActor »èÁ¦


	Super::DestroyItem();
}

void UCWeaponItem::SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter, float InActionDamage, FCustomDamageEvent InDamageEvent)
{
	InActionDamage += UKismetMathLibrary::RandomFloatInRange(MinDamage, MaxDamage);

	InOtherCharacter->TakeDamage(InActionDamage, InDamageEvent, InAttacker->GetController(), InAttackCauser);
}

void UCWeaponItem::Do_Action(class ACharacter* InOwner, FKey InKey)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->DoAction(InKey);
}

void UCWeaponItem::BeginDoAction(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->BeginDoAction();
}

void UCWeaponItem::EndDoAction(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->EndDoAction();
}

void UCWeaponItem::OnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->OnHands();
}

void UCWeaponItem::BeginOnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->Begin_OnHands();
}

void UCWeaponItem::EndOnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->End_OnHands();
}

void UCWeaponItem::OnDoActionBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackerCauser, class ACharacter* InOtherCharacter, float InActionDamage, FCustomDamageEvent InDamageEvent)
{
	SendDamage(InAttacker, InAttackerCauser, InOtherCharacter, InActionDamage, InDamageEvent);
}

void UCWeaponItem::DropItem(FVector InDropPosition)
{
	Super::DropItem(InDropPosition);

	DoAction->SetOwnerCharacter(NULL);
	Equipment->SetOwnerCharacter(NULL);
	EquipActor->SetOwnerCharacter(NULL);
	EquipActor->SetVisibility(false);
}

void UCWeaponItem::PickUpItem(class ACharacter* InOwner)
{
	Super::PickUpItem(InOwner);

	DoAction->SetOwnerCharacter(InOwner);
	Equipment->SetOwnerCharacter(InOwner);
	EquipActor->SetOwnerCharacter(InOwner);

	/*UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(InOwner);

	CheckNull(equip);

	if (!(equip->GetWeapon()))
	{
		equip->EquipItem(this);
	}*/
}