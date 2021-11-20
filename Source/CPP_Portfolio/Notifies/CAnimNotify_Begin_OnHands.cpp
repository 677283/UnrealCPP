#include "CAnimNotify_Begin_OnHands.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Item/Equip/Weapon/CEquipment.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Components/CEquipComponent.h"

FString UCAnimNotify_Begin_OnHands::GetNotifyName_Implementation() const
{
	return "Begin_OnHands";
}

void UCAnimNotify_Begin_OnHands::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());

	CheckNull(equip);
	equip->GetWeapon()->GetEquipment()->Begin_OnHands();
}