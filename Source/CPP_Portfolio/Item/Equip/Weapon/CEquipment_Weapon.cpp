#include "CEquipment_Weapon.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Item/Equip/Weapon/CEquipActor.h"


void UCEquipment_Weapon::BeginPlay(ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	bHands = false;
}

void UCEquipment_Weapon::Equip()
{
	Super::Equip();

	if (OnEquip.IsBound())
		OnEquip.Broadcast();
	OffHands();
}

void UCEquipment_Weapon::Unequip()
{
	Super::Unequip();
	if (OnUnequip.IsBound())
		OnUnequip.Broadcast();
}

void UCEquipment_Weapon::OnHands()
{
	CheckFalse(State->IsStateIdle());
	if (!EquipMontage)
	{
		Begin_OnHands();
		End_OnHands();
		return;
	}
	State->SetStateEquip();
	OwnerCharacter->PlayAnimMontage(EquipMontage, EquipPlayRatio);
}

void UCEquipment_Weapon::Begin_OnHands()
{
	bHands = true;
	CheckFalse(EquipSocket.GetStringLength() > 0);
	if (OnEquipmentToggleHands.IsBound())
		OnEquipmentToggleHands.Broadcast(EquipSocket);
}

void UCEquipment_Weapon::End_OnHands()
{
	State->SetStateIdle();
}

void UCEquipment_Weapon::OffHands()
{
	CheckFalse(State->IsStateIdle());
	bHands = false;
	CheckFalse(UnequipSocket.GetStringLength() > 0);
	if (OnEquipmentToggleHands.IsBound())
		OnEquipmentToggleHands.Broadcast(UnequipSocket);
}

void UCEquipment_Weapon::ToggleHands()
{
	if (bHands)
		OffHands();
	else
		OnHands();
}