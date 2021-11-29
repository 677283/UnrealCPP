#include "CEquipComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#define TESTMODE

UCEquipComponent::UCEquipComponent()
{
	
}


void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCEquipComponent::EquipItem(UCEquipAsset* InItem)
{
	CheckNull(InItem);

	switch (InItem->GetEquipType())
	{
	case EEquipType::Weapon:
		if (!!Weapon)
		{
			//TODO ÀåÂøÁß ¹«±â ÀÖÀ»¶§
		}
		else
		{
			if (OnEquip.IsBound())
				OnEquip.Broadcast(InItem);
			Weapon = Cast<UCWeaponAsset>(InItem);
			//Weapon->GetEquipment()->Equip();
		}
		break;
	case EEquipType::Armor:
		//TODO °©¿Ê ÀåÂø
		break;
	}

}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}