#include "CWidget_SkillTree_Slot.h"
#include "Global.h"
#include "Skill/CSkill.h"
#include "Components/CSkillComponent.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"

void UCWidget_SkillTree_Slot::NativeConstruct()
{
	bActive = false;

	UButton* btn = Cast<UButton>(GetWidgetFromName("SKILL_BTN"));

	CheckNull(btn);
	UpdateSlot();

	btn->OnClicked.AddDynamic(this, &UCWidget_SkillTree_Slot::OnClicked);

	SkillComponent = CHelpers::GetComponent<UCSkillComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

//FReply UCWidget_SkillTree_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//	CheckFalseResult(SkillComponent->GetSkillPoint() > 0, reply);
//
//	return reply;
//}

void UCWidget_SkillTree_Slot::UpdateSlot()
{
	for (FSkillTreeData info : NeedSkillInfo)
	{
		TSubclassOf<UCSkill> skillClass = info.OtherSlot->GetSkillClass();
		CheckTrue(info.NeedSkillLevel > SkillComponent->LevelCheck(skillClass));
	}

	//Todo Buttn Active

	bActive = true;
}

void UCWidget_SkillTree_Slot::OnClicked()
{
	CheckFalse(SkillComponent->GetSkillPoint() > 0);
	CheckFalse(bActive);

	if (SkillComponent->LevelCheck(Skill) == -1)
	{
		UCSkill* skill = NewObject<UCSkill>(Skill);
		SkillComponent->AddSkill(skill);
	}
	else
	{
		SkillComponent->GetSkill(Skill)->SkillLevelUp();
	}
}