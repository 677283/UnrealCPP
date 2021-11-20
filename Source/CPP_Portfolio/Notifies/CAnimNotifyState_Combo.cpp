#include "CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CDoAction.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
	return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());
	CheckNull(equip);
	equip->GetWeapon()->GetDoAction()->OnCombo();

}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());
	CheckNull(equip);
	equip->GetWeapon()->GetDoAction()->OffCombo();
}