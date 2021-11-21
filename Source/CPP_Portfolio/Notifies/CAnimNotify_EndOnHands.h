#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndOnHands.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimNotify_EndOnHands : public UAnimNotify
{
	GENERATED_BODY()
private:
	FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
};
