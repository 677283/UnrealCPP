#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_QuickSlot.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void ActiveSlot(int32 InIndex);

private:
	void OnDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);

	void InventoryDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);
	void SkillTreeDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);

private:
	TArray<class UCWidget_Slot*> Slots;
};
