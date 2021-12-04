#include "CEquipComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"

UCEquipComponent::UCEquipComponent()
{
	
}


void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCEquipComponent::EquipItem(UCEquipItem* InItem)
{
	CheckNull(InItem);

	switch (InItem->GetEquipType())
	{
	case EEquipType::Weapon:
		if (!!Weapon)
		{
			//TODO ������ ���� ������
		}
		else
		{
			if (OnEquip.IsBound())
				OnEquip.Broadcast(InItem);
			Weapon = Cast<UCWeaponItem>(InItem);
			//Weapon->GetEquipment()->Equip();
		}
		break;
	case EEquipType::Armor:
		//TODO ���� ����
		break;
	}

}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}