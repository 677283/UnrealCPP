#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

ACEnemy_AI::ACEnemy_AI()
{

}

void ACEnemy_AI::MoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetActorRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACEnemy_AI::MoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0, GetActorRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}