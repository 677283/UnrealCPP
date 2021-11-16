#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndDoSkill.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimNotify_EndDoSkill : public UAnimNotify
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		FName SkillName;
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
