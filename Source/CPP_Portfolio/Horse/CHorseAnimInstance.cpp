#include "CHorseAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"

void UCHorseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCHorseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	
	Direction = OwnerCharacter->GetActorRotation().Yaw - LastRotate.Yaw;
	float abs = UKismetMathLibrary::Abs(Direction);
	if (abs > 100)
		Direction *= -1;

	LastRotate = OwnerCharacter->GetActorRotation();
}