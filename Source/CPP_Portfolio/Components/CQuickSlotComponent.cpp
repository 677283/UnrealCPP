#include "Components/CQuickSlotComponent.h"
#include "Global.h"
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

void UCQuickSlotComponent::RegisterSlot(int32 InIndex, UObject* InObject)
{
	CheckNull(InObject);
	CheckFalse(InIndex > -1 && InIndex < SlotList.Num());

	SlotList[InIndex] = InObject;
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