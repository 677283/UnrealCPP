#include "CAnimNotify_BeginDoSkill.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CSkillComponent.h"
#include "Skill/CSkill.h"

FString UCAnimNotify_BeginDoAction::GetNotifyName_Implementation() const
{
	return "Begin_DoSkill";
}

void UCAnimNotify_BeginDoAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(MeshComp->GetOwner());

	CheckNull(equip);
	equip->GetWeapon()->GetDoAction()->BeginDoAction();
}
