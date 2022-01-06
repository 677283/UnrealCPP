#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_SkillTree_Tab.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree_Tab : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

public:
	UFUNCTION(BlueprintCallable)
		void SkillTreeDrawLine(FPaintContext InContext);

private:
	void OnSlotDoubleClick(class UCWidget_Slot* InSlot);

private:
	TArray<class UCWidget_Slot_SkillTree*> Slots;
	class UCSkillComponent* SkillComponent;
	bool bActive;
};
