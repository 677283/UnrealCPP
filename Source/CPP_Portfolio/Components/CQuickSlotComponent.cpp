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
	DelegateHandles.SetNum(MaxSlotCount);
}

void UCQuickSlotComponent::RegisterSlot(int32 InIndex, UObject* InObject)
{
	CheckNull(InObject);
	CheckFalse(InIndex > -1 && InIndex < SlotList.Num());

	if (!!SlotList[InIndex])
	{
		UCItem* item = Cast<UCItem>(SlotList[InIndex]);

		if (!!item)
		{
			item->OnDestroyItem.Remove(DelegateHandles[InIndex]);
		}
	}

	SlotList[InIndex] = InObject;

	UCItem* item = Cast<UCItem>(InObject);
	if (!!item)
	{
		DelegateHandles[InIndex] = item->OnDestroyItem.AddUObject(this, &UCQuickSlotComponent::OnDestroyItem);
	}
}

void UCQuickSlotComponent::UseSlot(int32 InIndex)
{
	UCItem* item = Cast<UCItem>(SlotList[InIndex]);

	if (!!item)
	{
		item->UseItem();

		return;
	}

	UCSkill* skill = Cast<UCSkill>(SlotList[InIndex]);

	if (!!skill)
	{
		skill->DoSkill();
		return;
	}

}

void UCQuickSlotComponent::OnUpdateItem(UCItem * InItem)
{

}

void UCQuickSlotComponent::OnDestroyItem(UCItem* InItem)
{
	int32 index = SlotList.Find(InItem);

	SlotList[index] = nullptr;
}
