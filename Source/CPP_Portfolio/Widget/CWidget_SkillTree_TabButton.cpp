#include "CWidget_SkillTree_TabButton.h"

void UCWidget_SkillTree_TabButton::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

FReply UCWidget_SkillTree_TabButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	OnToggleTab.ExecuteIfBound(Tab);

	return reply;
}