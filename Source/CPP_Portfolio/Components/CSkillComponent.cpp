#include "CSkillComponent.h"
#include "Global.h"
#include "Skill/CSkill.h"
#include "Widget/CWidget_SkillTree.h"
#include "GameFramework/Character.h"

UCSkillComponent::UCSkillComponent()
{
	CHelpers::GetClass(&SkillTreeWidgetClass, "WidgetBlueprint'/Game/__ProjectFile/Widgets/SkillTree/WB_SkillTree.WB_SkillTree_C'");
}

void UCSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	SkillTreeWidget = CreateWidget<UCWidget_SkillTree, APlayerController>(OwnerCharacter->GetController<APlayerController>(), SkillTreeWidgetClass, "SkillTree");
	SkillTreeWidget->AddToViewport();
	SkillTreeWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UCSkillComponent::AddSkill(class UCSkill* InSkill)
{
	CheckNull(InSkill);
	InSkill->BeginPlay(Cast<ACharacter>(GetOwner()));
	Skills.Add(InSkill->GetSkillName(), InSkill);
}

UCSkill* UCSkillComponent::GetSkill(FName InSkillName)
{
	if (!Skills.Find(InSkillName)) return nullptr;
	return *(Skills.Find(InSkillName));
}

UCSkill* UCSkillComponent::GetSkill(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNullResult(InSkillClass, nullptr);
	for (auto& skill : Skills)
	{
		if(InSkillClass->IsChildOf(skill.Value->GetClass()))
			return skill.Value;
	}

	return nullptr;
}

void UCSkillComponent::WidgetToggle()
{
	if (SkillTreeWidget->IsVisible())
	{
		OwnerCharacter->GetController<APlayerController>()->SetShowMouseCursor(false);
		OwnerCharacter->GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());
		SkillTreeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		OwnerCharacter->GetController<APlayerController>()->SetShowMouseCursor(true);

		FInputModeGameAndUI mode;
		mode.SetHideCursorDuringCapture(false);
		mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		OwnerCharacter->GetController<APlayerController>()->SetInputMode(mode);

		SkillTreeWidget->SetVisibility(ESlateVisibility::Visible);
		SkillTreeWidget->SetFocus();
	}
}

int32 UCSkillComponent::LevelCheck(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNullResult(InSkillClass, -1);
	for (auto& skill : Skills)
	{
		if (InSkillClass->IsChildOf(skill.Value->GetClass()))
			return skill.Value->GetSkillLevel();
	}

	return -1;
}

void UCSkillComponent::SkillLevelUp(TSubclassOf<class UCSkill> InSkillClass)
{
	CheckNull(InSkillClass);

	GetSkill(InSkillClass)->SkillLevelUp();
	SkillPoint--;
}