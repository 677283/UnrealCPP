#include "CWeaponAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
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

void UCWeaponAsset::BeginPlay(AActor* InOwner)
{
	CheckNull(EquipActorClass);

	Super::BeginPlay(InOwner);

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	EquipActor = OwnerCharacter->GetWorld()->SpawnActor<ACEquipActor>(EquipActorClass, params);

	ACharacter* Owner = Cast<ACharacter>(OwnerCharacter);

	CheckNull(EquipmentClass);
	Equipment = NewObject<UCEquipment_Weapon>(this, EquipmentClass);
	Equipment->BeginPlay(Owner);
	Equipment->OnEquipmentToggleHands.AddDynamic(EquipActor, &ACEquipActor::AttachTo);

	CheckNull(DoActionClass);
	DoAction = NewObject<UCDoAction>(this, DoActionClass);
	DoAction->BeginPlay(Owner);
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