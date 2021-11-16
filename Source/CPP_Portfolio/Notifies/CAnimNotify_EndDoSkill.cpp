#include "CAnimNotify_EndDoSkill.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CSkillComponent.h"
#include "Skill/CSkill.h"
#include "Animation/AnimSequenceBase.h"

FString UCAnimNotify_EndDoSkill::GetNotifyName_Implementation() const
{
	return "End_DoSkill";
}

void UCAnimNotify_EndDoSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCSkillComponent* skillcomp = CHelpers::GetComponent<UCSkillComponent>(MeshComp->GetOwner());

	CheckNull(skillcomp);

	UCSkill* skill = skillcomp->GetSkill(SkillName);

	CheckNull(skill);

	skill->EndDoSkill();
	
}
