#include "CWeaponAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "Item/Equip/Weapon/CDoAction_DoubleCombo.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponItem.h"

UCWeaponAsset::UCWeaponAsset()
{
	SetEquipType(EEquipType::Weapon);

	EquipActorClass = ACEquipActor::StaticClass();
	DoActionClass = UCDoAction::StaticClass();
	EquipmentClass = UCEquipment_Weapon::StaticClass();
}

UCItem* UCWeaponAsset::CreateItem(class ACharacter* InOwner, UCItem* InItem)
{
	UCWeaponItem* weaponItem;

	if (!InItem)
	{
		weaponItem = NewObject<UCWeaponItem>();
	}
	else
	{
		weaponItem = Cast<UCWeaponItem>(InItem);
	}

	Super::CreateItem(InOwner, weaponItem);

	CheckNullResult(EquipActorClass, NULL);
	FActorSpawnParameters params;
	params.Owner = InOwner;
	ACEquipActor* equipActor = InOwner->GetWorld()->SpawnActor<ACEquipActor>(EquipActorClass, params);

	CheckNullResult(EquipmentClass, NULL);
	UCEquipment_Weapon* equipment = NewObject<UCEquipment_Weapon>(this, EquipmentClass);
	equipment->BeginPlay(InOwner);
	equipment->OnEquipmentToggleHands.AddDynamic(equipActor, &ACEquipActor::AttachTo);
	equipment->OnEquip.AddDynamic(equipActor, &ACEquipActor::Equip);
	equipment->OnUnequip.AddDynamic(equipActor, &ACEquipActor::Unequip);

	CheckNullResult(DoActionClass, NULL);
	UCDoAction* doAction = NewObject<UCDoAction>(this, DoActionClass);
	doAction->BeginPlay(InOwner);
	doAction->OnDoActionBeginOverlap.AddDynamic(weaponItem, &UCWeaponItem::OnDoActionBeginOverlap);
	doAction->InitHands(equipment->GetHands());
	equipActor->OnEquipActorBeginOverlap.AddDynamic(doAction, &UCDoAction::OnEquipActorBeginOverlap);

	if (MinDamage < MaxDamage)
	{
		float temp = MinDamage;
		MinDamage = MaxDamage;
		MaxDamage = temp;
	}

	weaponItem->InitializeWeaponItem(equipActor, doAction, equipment, WeaponType, MinDamage, MaxDamage);

	return weaponItem;
}