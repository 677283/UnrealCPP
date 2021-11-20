#include "CEquipAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"

UCEquipAsset::UCEquipAsset()
{
	SetType(EItemType::Equip);
}

void UCEquipAsset::BeginPlay(ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

}

void UCEquipAsset::UseItem()
{
	if (bEquipping)
		Equip();
	else
		Unequip();
}

void UCEquipAsset::Equip()
{
	bEquipping = true;
}

void UCEquipAsset::Unequip()
{
	bEquipping = false;
}