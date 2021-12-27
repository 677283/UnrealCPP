#include "CWidget_SkillTree_Tab.h"
#include "Global.h"
#include "Widget/CWidget_SkillTree_Slot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"

void UCWidget_SkillTree_Tab::NativeConstruct()
{
	TArray<UWidget*> widgets;

	SetVisibility(ESlateVisibility::Hidden);

	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_SkillTree_Slot* slot = Cast<UCWidget_SkillTree_Slot>(widget);

		if (!slot) continue;

		Slots.Add(slot);
	}
}

int32 UCWidget_SkillTree_Tab::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	int32 returnInt = Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	FPaintContext context = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	for (UCWidget_SkillTree_Slot* slot : Slots)
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
	for (UCWidget_SkillTree_Slot* slot : Slots)
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