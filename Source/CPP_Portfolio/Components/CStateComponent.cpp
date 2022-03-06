#include "CStateComponent.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"

UCStateComponent::UCStateComponent()
{

}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCStateComponent::SetStateHitted()
{
	State = EStateType::Hitted;

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());

	CheckNull(equip);
	CheckNull(equip->GetWeapon());

	equip->GetWeapon()->ResetWeapon();
}
