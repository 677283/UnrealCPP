#include "CWeaponAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"

UCWeaponAsset::UCWeaponAsset()
{
	SetEquipType(EEquipType::Weapon);

	EquipActorClass = ACEquipActor::StaticClass();
	DoActionClass = UCDoAction::StaticClass();
	EquipmentClass = UCEquipment_Weapon::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner)
{
	CheckNull(EquipActorClass);

	Super::BeginPlay(InOwner);

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	EquipActor = OwnerCharacter->GetWorld()->SpawnActor<ACEquipActor>(EquipActorClass, params);

	CheckNull(EquipmentClass);
	Equipment = NewObject<UCEquipment_Weapon>(this, EquipmentClass);
	Equipment->BeginPlay(InOwner);
	Equipment->OnEquipmentToggleHands.AddDynamic(EquipActor, &ACEquipActor::AttachTo);
	Equipment->OnEquip.AddDynamic(EquipActor, &ACEquipActor::Equip);
	Equipment->OnUnequip.AddDynamic(EquipActor, &ACEquipActor::Unequip);
	bOnHands = Equipment->GetHands();

	CheckNull(DoActionClass);
	DoAction = NewObject<UCDoAction>(this, DoActionClass);
	DoAction->BeginPlay(InOwner);
	DoAction->OnDoActionBeginOverlap.AddDynamic(this, &UCWeaponAsset::OnDoActionBeginOverlap);
	DoAction->InitHands(Equipment->GetHands());

	EquipComponent = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
}

void UCWeaponAsset::UseItem()
{
	EquipComponent = CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter);
	CheckNull(EquipComponent);
	Equipment->Equip();
	EquipComponent->EquipItem(this);
}

void UCWeaponAsset::SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter,float InActionDamage)
{
	float damage = 0;
	//TODO 데미지 계산
	FCustomDamageEvent damageType;
	//TODO 데미지타입 입력;

	InOtherCharacter->TakeDamage(damage, damageType, InAttacker->GetController(), InAttackCauser);
}

void UCWeaponAsset::Do_Action(class ACharacter* InOwner, FKey InKey)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->DoAction(InKey);
}

void UCWeaponAsset::BeginDoAction(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->BeginDoAction();
}

void UCWeaponAsset::EndDoAction(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	DoAction->EndDoAction();
}

void UCWeaponAsset::OnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->OnHands();
}

void UCWeaponAsset::BeginOnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->Begin_OnHands();
}

void UCWeaponAsset::EndOnHands(class ACharacter* InOwner)
{
	CheckFalse(OwnerCharacter == InOwner);
	Equipment->End_OnHands();
}

void UCWeaponAsset::OnDoActionBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackerCauser, class ACharacter* InOtherCharacter, float InActionDamage)
{
	SendDamage(InAttacker, InAttackerCauser, InOtherCharacter, InActionDamage);
}

void UCWeaponAsset::DropItem(FVector InDropPosition)
{
	Super::DropItem(InDropPosition);

	DoAction->SetOwnerCharacter(NULL);
	Equipment->SetOwnerCharacter(NULL);
	EquipActor->SetOwnerCharacter(NULL);
	EquipActor->SetVisibility(false);
}

void UCWeaponAsset::PickUpItem(class ACharacter* InOwner)
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