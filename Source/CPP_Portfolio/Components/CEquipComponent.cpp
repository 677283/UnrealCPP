#include "CEquipComponent.h"
#include "Global.h"
#include "Items/Equip/Weapon/CWeaponAsset.h"
#include "Items/Equip/Weapon/CEquipment.h"
#define TESTMODE

UCEquipComponent::UCEquipComponent()
{
	
}


void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

UCEquipAsset* UCEquipComponent::EquipItem(UCEquipAsset* InItem)
{
	CheckNullResult(InItem,NULL);
	UCEquipAsset* outEquip = NULL;

	switch (InItem->GetEquipType())
	{
	case EEquipType::Weapon:
		if (!!Weapon)
		{
			//TODO
			/*if (Weapon->IsHands())
			{
				Weapon->OffHands();
				Weapon->Unequip();
				outEquip = Weapon;
				
				Weapon = Cast<UCWeaponAsset>(InItem);
				Weapon->Equip();
				Weapon->Begin_OnHands();
			}
			else
			{
				Weapon->Unequip();
				outEquip = Weapon;

				Weapon = Cast<UCWeaponAsset>(InItem);
				Weapon->Equip();
			}*/
		}
		else
		{
			Weapon = Cast<UCWeaponAsset>(InItem);
			Weapon->GetEquipment()->Equip();
			bOnHands = Weapon->GetEquipment()->GetHands();
		}
		break;
	case EEquipType::Armor:
		//TODO
		break;
	}

	return outEquip;
}