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
		if (OnEquip.IsBound())
			OnEquip.Broadcast(InItem, Weapon);

		Weapon = Cast<UCWeaponItem>(InItem);
		
		UTexture2D* icon;
		!!Weapon ? icon = Weapon->GetIcon() : icon = nullptr;
		OnUpdateIcon.ExecuteIfBound("Weapon", icon);
		break;
	case EEquipType::Armor:
		//TODO °©¿Ê ÀåÂø
		break;
	}
}

void UCEquipComponent::UnequipItem(FString InName)
{
	if (InName == "Weapon")
	{
		if(OnUnequip.IsBound())
			OnUnequip.Broadcast(nullptr, Weapon);
		Weapon = nullptr;

		OnUpdateIcon.ExecuteIfBound("Weapon", nullptr);
	}

}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}