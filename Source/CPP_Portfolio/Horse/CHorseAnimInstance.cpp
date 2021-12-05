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
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	
	FVector forward = OwnerCharacter->GetActorForwardVector();

	float angle = UKismetMathLibrary::Dot_VectorVector(forward, PreviousForward);

	angle = UKismetMathLibrary::Acos(angle);

	PreviousForward = forward;

	CLog::Log(angle);
}