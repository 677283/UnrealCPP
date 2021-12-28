#include "CSkill_Active.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "GameFramework/Character.h"

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
	if (bNeedWeapon) //무기를 들고 있어야 하는가?
	{
		CheckNullResult(Equip->GetWeapon(), false);
		if (!Equip->IsHandsOn()) //무기를 들고 있는가?
			return false;
		if (NeedWeaponTypes.Num() > 0)
		{
			int32 typeSum = 0;
			int32 weaponType = (int32)Equip->GetWeapon()->GetWeaponType();

			
			for (EWeaponType type : NeedWeaponTypes)
			{
				typeSum += pow(2, (int32)type);
			}

			if (!(typeSum | weaponType))
				return false;
		}
	}

	return true;
}

void UCSkill_Active::SendDamage(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter, float InActionDamage, FCustomDamageEvent InDamageEvent)
{
	InOtherCharacter->TakeDamage(InActionDamage, InDamageEvent, InAttacker->GetController(), InAttackCauser);
}