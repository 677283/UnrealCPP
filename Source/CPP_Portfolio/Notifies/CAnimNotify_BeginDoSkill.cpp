#include "CAnimNotify_BeginDoSkill.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CSkillComponent.h"
#include "Skill/CSkill.h"

FString UCAnimNotify_BeginDoSkill::GetNotifyName_Implementation() const
{
	return "Begin_DoSkill";
}

void UCAnimNotify_BeginDoSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCSkillComponent* skillcomp = CHelpers::GetComponent<UCSkillComponent>(MeshComp->GetOwner());

	CheckNull(skillcomp);

	UCSkill* skill = skillcomp->GetSkill(SkillName);

	CheckNull(skill);

	skill->BeginDoSkill();
}
