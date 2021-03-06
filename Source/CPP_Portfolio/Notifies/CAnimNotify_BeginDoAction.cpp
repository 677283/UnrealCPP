#include "CAnimNotify_BeginDoAction.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "Components/CEquipComponent.h"

FString UCAnimNotify_BeginDoAction::GetNotifyName_Implementation() const
{
	return "Begin_DoAction";
}

void UCAnimNotify_BeginDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());

	CheckNull(equip);
	//equip->GetWeapon()->GetDoAction()->BeginDoAction();
	ACharacter* owner = Cast<ACharacter>(MeshComp->GetOwner());
	CheckNull(owner);
	equip->GetWeapon()->BeginDoAction(owner);
}
