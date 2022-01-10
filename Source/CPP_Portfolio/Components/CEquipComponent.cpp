#include "CEquipComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Widget/CWidget_Equip.h"
#include "GameFramework/Character.h"
#include "Widget/CWidget_HUD.h"
#include "Player/CPlayer.h"
#include "Components/PanelWidget.h"

#include "Components/CanvasPanelSlot.h"

UCEquipComponent::UCEquipComponent()
{

}

void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

void UCEquipComponent::EquipItem(UCEquipItem* InItem)
{
	CheckNull(InItem);

	switch (InItem->GetEquipType())
	{
	case EEquipType::Weapon:
		if (!!Weapon && !SubWeapon)
		{

		}
		else
		{
			OnEquip.ExecuteIfBound(InItem, Weapon);

			OnEquipWidget.ExecuteIfBound("Weapon", InItem);

			Weapon = Cast<UCWeaponItem>(InItem);
		}
		
		break;
	}
}

void UCEquipComponent::EquipSubWeapon(UCEquipItem * InItem)
{

}

void UCEquipComponent::UnequipItem(FString InName)
{
	if (InName == "Weapon")
	{
		if (!Weapon) return;

		if (OnUnequip.IsBound())
		{
			if (OnUnequip.Execute(Weapon))
			{
				Weapon = nullptr;
				OnEquipWidget.ExecuteIfBound("Weapon", nullptr);
			}
		}
	}
}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}
