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

#define WEAPON 0
#define SUBWEAPON 1

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
			OnEquip.ExecuteIfBound(InItem, SubWeapon);
			
			OnEquipWidget.ExecuteIfBound(SUBWEAPON, InItem);
			
			SubWeapon = Cast<UCWeaponItem>(InItem);
		}
		else
		{
			OnEquip.ExecuteIfBound(InItem, Weapon);
			InItem->UseItem();
			OnEquipWidget.ExecuteIfBound(WEAPON, InItem);
			if (!!Weapon)
				Weapon->Unequip();
			Weapon = Cast<UCWeaponItem>(InItem);
		}
		
		break;
	}
}

void UCEquipComponent::EquipItem(int32 InIndex, UCEquipItem * InItem)
{
	CheckNull(InItem);

	switch (InIndex)
	{
		case WEAPON:
			OnEquip.ExecuteIfBound(InItem, Weapon);
			InItem->UseItem();
			OnEquipWidget.ExecuteIfBound(SUBWEAPON, InItem);
			Weapon->Unequip();
			Weapon = Cast<UCWeaponItem>(InItem);
			break;
		
		case SUBWEAPON:
			OnEquip.ExecuteIfBound(InItem, SubWeapon);

			OnEquipWidget.ExecuteIfBound(SUBWEAPON, InItem);

			SubWeapon = Cast<UCWeaponItem>(InItem);
			break;
	}
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
				OnEquipWidget.ExecuteIfBound(0, nullptr);
			}
		}
	}
	else if (InName == "SubWeapon")
	{
		if (!SubWeapon) return;

		if (OnUnequip.IsBound())
		{
			if (OnUnequip.Execute(SubWeapon))
			{
				SubWeapon = nullptr;
				OnEquipWidget.ExecuteIfBound(1, nullptr);
			}
		}
	}
}

void UCEquipComponent::SwapWeapon()
{
	CheckFalse(!!Weapon && !!SubWeapon);
	UCWeaponItem* temp = SubWeapon;
	Weapon->Unequip();
	SubWeapon->Equip();
	SubWeapon->GetEquipment()->Begin_OnHands();
	SubWeapon = Weapon;
	Weapon = temp;
}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}
