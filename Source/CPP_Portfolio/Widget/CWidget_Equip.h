#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Equip.generated.h"

UENUM()
enum class EEquipSlot : uint8
{
	Helmet, Top, Bottoms, Weapon, Weapon_Sub, Boot, Max,
};

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Equip : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetSlotIcon(EEquipSlot InIndex, class UTexture2D* InIcon);

private:
	TArray<class UCWidget_Equip_Slot*> Slots;
};
