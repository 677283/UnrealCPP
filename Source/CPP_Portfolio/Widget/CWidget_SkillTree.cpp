#include "CWidget_SkillTree.h"
#include "Global.h"
#include "Widget/CWidget_SkillTree_TabButton.h"
#include "Blueprint/WidgetTree.h"

void UCWidget_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	SetVisibility(ESlateVisibility::Hidden);

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_SkillTree_TabButton* button = Cast<UCWidget_SkillTree_TabButton>(widget);

		if (!button) continue;

		button->OnToggleTab.BindUObject(this, &UCWidget_SkillTree::OnToggleTab);
		if (!ActiveTab)
			ActiveTab = button->GetTab();
	}
	ActiveTab->SetVisibility(ESlateVisibility::Visible);
}

void UCWidget_SkillTree::OnToggleTab(class UWidget* InTab)
{
	CheckNull(InTab);
	if (ActiveTab != InTab)
	{
		ActiveTab->SetVisibility(ESlateVisibility::Hidden);
		ActiveTab = InTab;
		ActiveTab->SetVisibility(ESlateVisibility::Visible);
	}

}