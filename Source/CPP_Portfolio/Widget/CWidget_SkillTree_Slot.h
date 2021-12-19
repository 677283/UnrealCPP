#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_SkillTree_Slot.generated.h"

USTRUCT(BlueprintType)
struct FSkillTreeData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCWidget_SkillTree_Slot* OtherSlot;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 NeedSkillLevel;
};

UCLASS()
class CPP_PORTFOLIO_API UCWidget_SkillTree_Slot : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSkill> Skill;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FSkillTreeData> NeedSkillInfo;

protected:
	virtual void NativeConstruct() override;
	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
private:
	void UpdateSlot();
	void OnClicked();

public:
	FORCEINLINE TSubclassOf<class UCSkill> GetSkillClass() { return Skill; }

private:
	class ACharacter* OwnerCharacter;
	class UCSkillComponent* SkillComponent;
	bool bActive;
};
