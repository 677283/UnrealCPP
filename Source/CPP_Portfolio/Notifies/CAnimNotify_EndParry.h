#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndParry.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimNotify_EndParry : public UAnimNotify
{
	GENERATED_BODY()
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
