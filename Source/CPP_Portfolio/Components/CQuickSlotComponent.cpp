#include "Components/CQuickSlotComponent.h"
#include "Item/CItem.h"
#include "Skill/CSkill.h"

UCQuickSlotComponent::UCQuickSlotComponent()
{

}


void UCQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	SlotList.SetNum(MaxSlotCount);
}

void UCQuickSlotComponent::UseSlot(int32 InIndex)
{
	UCItem* item = Cast<UCItem>(SlotList[InIndex]);

	if (!!item)
	{
		item->UseItem();

		if (item->GetAmount() < 1)
			SlotList[InIndex] = nullptr;
		return;
	}

	UCSkill* skill = Cast<UCSkill>(SlotList[InIndex]);

	if (!!skill)
	{
		skill->DoSkill();
		return;
	}

}