#include "CAnimNotifyState_Collision.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Items/Equip/Weapon/CWeaponAsset.h"
#include "Items/Equip/Weapon/CEquipActor.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());
	CheckNull(equip);
	equip->GetWeapon()->GetEquipActor()->OnCollision();

}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());
	CheckNull(equip);
	equip->GetWeapon()->GetEquipActor()->OffCollision();
}