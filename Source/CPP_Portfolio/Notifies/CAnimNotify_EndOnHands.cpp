#include "CAnimNotify_EndOnHands.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Components/CEquipComponent.h"

FString UCAnimNotify_EndOnHands::GetNotifyName_Implementation() const
{
	return "End_OnHands";
}

void UCAnimNotify_EndOnHands::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());

	CheckNull(equip);
	//equip->GetWeapon()->GetEquipment()->End_OnHands();
	ACharacter* owner = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(owner);
	equip->GetWeapon()->EndOnHands();
}