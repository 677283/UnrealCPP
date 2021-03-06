#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_BeginDoSkill.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimNotify_BeginDoSkill : public UAnimNotify
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		FName SkillName;
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};