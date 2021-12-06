#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CHorseAnimInstance.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCHorseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Direction;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
	FRotator LastRotate;
};
