#include "CWidget_Slot_SkillTree.h"
#include "Global.h"
#include "Skill/CSkill.h"

void UCWidget_Slot_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	SlotData = NewObject<UCSkill>(this, Skill);

}