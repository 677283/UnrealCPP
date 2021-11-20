#include "Notifies/CAnimNotify_EndDoAction.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"

FString UCAnimNotify_EndDoAction::GetNotifyName_Implementation() const
{
	return "Begin_OnHands";
}

void UCAnimNotify_EndDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());

	CheckNull(equip);
	equip->GetWeapon()->GetDoAction()->EndDoAction();
}