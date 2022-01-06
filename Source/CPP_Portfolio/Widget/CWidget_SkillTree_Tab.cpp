#include "CWidget_SkillTree_Tab.h"
#include "Global.h"
#include "CWidget_Slot_SkillTree.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "GameFramework/Character.h"
#include "Components/CSkillComponent.h"
#include "Skill/CSkill.h"

void UCWidget_SkillTree_Tab::NativeConstruct()
{
	TArray<UWidget*> widgets;

	SetVisibility(ESlateVisibility::Hidden);

	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_Slot_SkillTree* slot = Cast<UCWidget_Slot_SkillTree>(widget);

		if (!slot) continue;
		Slots.Add(slot);
		slot->OnSlotDoubleClick.BindUObject(this, &UCWidget_SkillTree_Tab::OnSlotDoubleClick);
	}

	SkillComponent = CHelpers::GetComponent<UCSkillComponent>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

int32 UCWidget_SkillTree_Tab::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 returnInt = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	FPaintContext context = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	for (UCWidget_Slot_SkillTree* slot : Slots)
	{
		TArray<FSkillTreeData> datas = slot->GetNeedSkillInfo();

		FVector2D posA, posB;

		posA = slot->GetCachedGeometry().Position;
		posA.X += slot->GetDesiredSize().X / 2.0f;
		
		for (FSkillTreeData data : datas)
		{
			posB = data.OtherSlot->GetCachedGeometry().Position;
			posB.Y += data.OtherSlot->GetDesiredSize().Y;
			posB.X += data.OtherSlot->GetDesiredSize().X / 2.0f;

			UWidgetBlueprintLibrary::DrawLine
			(
				context,
				posA,
				posB,
				FLinearColor::Red
			);
		}
	}
	
	return returnInt;
}

void UCWidget_SkillTree_Tab::SkillTreeDrawLine(FPaintContext InContext)
{
//	if (!InContext) return;
	for (UCWidget_Slot_SkillTree* slot : Slots)
	{
		TArray<FSkillTreeData> datas = slot->GetNeedSkillInfo();

		FVector2D posA, posB;

		posA = slot->GetCachedGeometry().Position;
		posA.X += slot->GetDesiredSize().X / 2.0f;
		for (FSkillTreeData data : datas)
		{
			posB = data.OtherSlot->GetCachedGeometry().Position;
			posB.Y += data.OtherSlot->GetDesiredSize().Y;
			posB.X += data.OtherSlot->GetDesiredSize().X / 2.0f;

			UWidgetBlueprintLibrary::DrawLine
			(
				InContext,
				posA,
				posB,
				FLinearColor::Red
			);
		}
	}

}

void UCWidget_SkillTree_Tab::OnSlotDoubleClick(class UCWidget_Slot* InSlot)
{
	CheckFalse(SkillComponent->GetSkillPoint() > 0);
	//CheckFalse(bActive);

	UCSkill* skill = Cast<UCSkill>(InSlot->GetData());
	CheckNull(skill);

	//CLog::Log(SkillComponent->LevelCheck(skill->StaticClass()));

	if (SkillComponent->LevelCheck(skill->GetClass()) == -1)
	{
		SkillComponent->AddSkill(skill);
		SkillComponent->SkillLevelUp(skill->GetClass());
	}
	else
	{
		CheckNull(SkillComponent->GetSkill(skill->GetClass()));
		SkillComponent->SkillLevelUp(skill->GetClass());
	}
}