#include "CAnimNotify_SwapWeapon.h"
#include "Global.h"
#include "Player/CPlayer.h"

FString UCAnimNotify_SwapWeapon::GetNotifyName_Implementation() const
{
	return "SwapWeapon";
}

void UCAnimNotify_SwapWeapon::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::Notify(MeshComp, Animation);

	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	ACPlayer* player = Cast<ACPlayer>(MeshComp->GetOwner());

	CheckNull(player);

	player->SwapWeapon();
}
