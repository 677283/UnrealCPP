#include "CWidget_SkillTree.h"

void UCWidget_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;
	SetVisibility(ESlateVisibility::Hidden);
}