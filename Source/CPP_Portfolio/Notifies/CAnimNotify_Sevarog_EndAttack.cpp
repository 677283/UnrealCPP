#include "CAnimNotify_Sevarog_EndAttack.h"
#include "Global.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Components/CEquipComponent.h"

FString UCAnimNotify_Sevarog_EndAttack::GetNotifyName_Implementation() const
{
	return "Sevarog_EndAttack";
}

void UCAnimNotify_Sevarog_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACEnemy_AI_Boss* boss = Cast<ACEnemy_AI_Boss>(MeshComp->GetOwner());
	CheckNull(boss);
	boss->FinishPattern();

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(boss);
	CheckNull(equip);
	equip->GetWeapon()->ResetWeapon();
}

