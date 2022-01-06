#pragma once

#include "CoreMinimal.h"
#include "Widget/CWidget_Slot.h"
#include "CWidget_Slot_SkillTree.generated.h"

USTRUCT(BlueprintType)
struct FSkillTreeData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UCWidget_Slot_SkillTree* OtherSlot;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int32 NeedSkillLevel;
};

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Slot_SkillTree : public UCWidget_Slot
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, NoClear)
		TSubclassOf<class UCSkill> Skill;
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TArray<FSkillTreeData> NeedSkillInfo;

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE TArray<FSkillTreeData> GetNeedSkillInfo() { return NeedSkillInfo; }

};
