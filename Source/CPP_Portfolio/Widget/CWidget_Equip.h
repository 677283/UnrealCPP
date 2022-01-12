#pragma once

#include "CoreMinimal.h"
#include "Widget/CWidget_Window.h"
#include "CWidget_Equip.generated.h"

DECLARE_DELEGATE_TwoParams(FOnEquip_EquipWidget, int32, class UCEquipItem*);
DECLARE_DELEGATE_OneParam(FOnUnequip_EuipWidget, FString);
UCLASS()
class CPP_PORTFOLIO_API UCWidget_Equip : public UCWidget_Window
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	
	void OnDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);
	void OnSlotDoubleClick(class UCWidget_Slot* InSlot);
	void OnEquipWidget(int32 InIndex, UObject* InItem);

	void InventoryDataCheck(class UCWidget_Slot* UpSlot, class UCWidget_Slot* DownSlot);

private:
	TArray<class UCWidget_Slot*> Slots;

public:
	FOnEquip_EquipWidget OnEquip_EquipWidget;
	FOnUnequip_EuipWidget OnUnequip_EuipWidget;
};
