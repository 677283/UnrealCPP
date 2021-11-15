#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Items/Equip/Weapon/CEquipActor.h"


void UCEquipment::BeginPlay(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	bHands = false;
}

void UCEquipment::Equip()
{

}

void UCEquipment::Unequip()
{

}

void UCEquipment::OnHands()
{
	OwnerCharacter->PlayAnimMontage(EquipMontage, EquipPlayRatio);
}

void UCEquipment::Begin_OnHands()
{
	bHands = true;
	CheckFalse(EquipSocket.GetStringLength() > 0);
	if (OnEquipmentToggleHands.IsBound())
		OnEquipmentToggleHands.Broadcast(EquipSocket);
}

void UCEquipment::End_OnHands()
{

}

void UCEquipment::OffHands()
{
	bHands = false;
	CheckFalse(UnequipSocket.GetStringLength() > 0);
	if (OnEquipmentToggleHands.IsBound())
		OnEquipmentToggleHands.Broadcast(UnequipSocket);
}

void UCEquipment::ToggleHands()
{
	if (bHands)
		OffHands();
	else
		OnHands();
}