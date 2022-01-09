#include "CWidget_Slot_SkillTree.h"
#include "Global.h"
#include "Components/Image.h"
#include "Skill/CSkill.h"
#include "Interfaces/ISlotWidget.h"

#include "BluePrint/WidgetTree.h"
#include "Widget/CWidget_DragAndDrop.h"

void UCWidget_Slot_SkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	UCSkill* skill = NewObject<UCSkill>(this, Skill);
	SlotData = skill;

	skill->BeginPlay(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

FReply UCWidget_Slot_SkillTree::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	UCSkill* skill = Cast<UCSkill>(SlotData);
	
	CheckTrueResult(skill->GetSkillLevel() > 0, reply);
		
	SelectSlot = nullptr;
	DragAndDrop->SetActive(false);

	return reply;
}
