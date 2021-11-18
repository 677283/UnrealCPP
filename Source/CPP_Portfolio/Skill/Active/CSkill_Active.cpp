#include "CSkill_Active.h"
#include "Global.h"
#include "Components/CEquipComponent.h"

UCSkill_Active::UCSkill_Active()
{
	SetSkillType(ESkillType::Active);
}

void UCSkill_Active::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	State = CHelpers::GetComponent<UCStateComponent>(InOwner);
	Equip = CHelpers::GetComponent<UCEquipComponent>(InOwner);
}

void UCSkill_Active::DoSkill()
{
	Super::DoSkill();
}

bool UCSkill_Active::WeaponCheck()
{
	if (bNeedWeapon)
	{
		if (!Equip->IsHandsOn())
			return false;
		if (NeedWeaponType != EWeaponType::Max && Equip->GetWeapon()->GetWeaponType() != NeedWeaponType)
			return false;
	}

	return true;
}