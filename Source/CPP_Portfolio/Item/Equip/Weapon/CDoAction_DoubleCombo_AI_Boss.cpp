#include "CDoAction_DoubleCombo_AI_Boss.h"

void UCDoAction_DoubleCombo_AI_Boss::EndDoAction()
{
	FString tmp = ComboKey;
	Super::EndDoAction();
	ComboKey = tmp;
}

void UCDoAction_DoubleCombo_AI_Boss::ResetDoAction()
{
	ComboKey = "";
}
