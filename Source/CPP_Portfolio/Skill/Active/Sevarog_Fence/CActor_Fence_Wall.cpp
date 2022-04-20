#include "CActor_Fence_Wall.h"
#include "Global.h"

ACActor_Fence_Wall::ACActor_Fence_Wall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACActor_Fence_Wall::BeginPlay()
{
	Super::BeginPlay();
	FVector pos = GetActorLocation();
	pos.Z = -150;
	SetActorLocation(pos);
	UpSpeed = UKismetMathLibrary::RandomFloatInRange(50.0f, 100.0f);
	SetActorTickEnabled(false);

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([=]()
	{
		this->SetActorTickEnabled(true);
	}), UKismetMathLibrary::RandomFloatInRange(0.5f, 1.0f), false);

}

void ACActor_Fence_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector pos = GetActorLocation();
	pos.Z += UpSpeed * DeltaTime;
	SetActorLocation(pos);
	if (pos.Z >= 50)
	{
		SetActorTickEnabled(false);
		OnReadyWall.ExecuteIfBound();
	}
}

