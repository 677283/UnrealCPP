#include "CAnimNotify_EndDash.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Components/CEquipComponent.h"

FString UCAnimNotify_EndDash::GetNotifyName_Implementation() const
{
	return "End_Dash";
}

void UCAnimNotify_EndDash::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	CheckNull(player);

	player->OffDash();
}
