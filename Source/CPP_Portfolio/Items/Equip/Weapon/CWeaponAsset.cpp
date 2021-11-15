#include "CWeaponAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Items/Equip/Weapon/CEquipActor.h"
#include "Items/Equip/Weapon/CDoAction.h"
#include "Items/Equip/Weapon/CEquipment.h"

UCWeaponAsset::UCWeaponAsset()
{
	SetEquipType(EEquipType::Weapon);

	EquipActorClass = ACEquipActor::StaticClass();
	DoActionClass = UCDoAction::StaticClass();
	EquipmentClass = UCEquipment::StaticClass();
}

void UCWeaponAsset::BeginPlay(ACharacter* InOwner)
{
	CheckNull(EquipActorClass);

	Super::BeginPlay(InOwner);

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	EquipActor = OwnerCharacter->GetWorld()->SpawnActor<ACEquipActor>(EquipActorClass, params);

	CheckNull(EquipmentClass);
	Equipment = NewObject<UCEquipment>(this, EquipmentClass);
	Equipment->BeginPlay(OwnerCharacter);
	Equipment->OnEquipmentToggleHands.AddDynamic(EquipActor, &ACEquipActor::AttachTo);

	CheckNull(DoActionClass);
	DoAction = NewObject<UCDoAction>(this, DoActionClass);
	DoAction->BeginPlay(OwnerCharacter);
	DoAction->OnDoActionBeginOverlap.AddDynamic(this, &UCWeaponAsset::OnDoActionBeginOverlap);
	DoAction->InitHands(Equipment->GetHands());
}

void UCWeaponAsset::SendDamage(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter,float InActionDamage)
{
	float damage = 0;
	//TODO 데미지 계산
	FCustomDamageEvent damageType;
	//TODO 데미지타입 입력;

	InOtherCharacter->TakeDamage(damage, damageType, InAttacker->GetController(), InAttackCauser);
}

void UCWeaponAsset::OnDoActionBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackerCauser, class ACharacter* InOtherCharacter, float InActionDamage)
{
	SendDamage(InAttacker, InAttackerCauser, InOtherCharacter, InActionDamage);
}