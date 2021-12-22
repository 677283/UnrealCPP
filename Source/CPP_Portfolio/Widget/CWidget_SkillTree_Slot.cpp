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
	btn->WidgetStyle.Normal.SetResourceObject(Icon);
	btn->OnClicked.AddDynamic(this, &UCWidget_SkillTree_Slot::OnClicked);
	
	SkillComponent = CHelpers::GetComponent<UCSkillComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	
	UpdateSlot();
}

void UCWidget_SkillTree_Slot::SynchronizeProperties()
{
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}

void UCWidget_SkillTree_Slot::OnSynchronizeProperties_Implementation()
{
	// Override this event in Blueprint
}

void UCWidget_SkillTree_Slot::UpdateSlot()
{
	CheckNull(SkillComponent);
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
	CLog::Log(SkillComponent->GetSkillPoint());
	CheckFalse(bActive);
	if (SkillComponent->LevelCheck(Skill) == -1)
	{
		UCSkill* skill = NewObject<UCSkill>(this, Skill);
		SkillComponent->AddSkill(skill);
		CLog::Log("CreateSkill");
	}
	else
	{
		CheckNull(SkillComponent->GetSkill(Skill));
		SkillComponent->SkillLevelUp(Skill);
		CLog::Log("UpSkill");
	}
}