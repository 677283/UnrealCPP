#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Equip.generated.h"

DECLARE_DELEGATE_OneParam(FOnEquipAction, FString);

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Equip : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetSlotIcon(FString InName, class UTexture2D* InIcon);
	void OnSlotMouseButtonDouble(FString InName);

private:
	TMap<FString, class UCWidget_Equip_Slot*> Slots;
	
public:
	FOnEquipAction OnEquipAction;
};
