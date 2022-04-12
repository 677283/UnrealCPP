#include "CSubjugate_Actor.h"
#include "Global.h"

ACSubjugate_Actor::ACSubjugate_Actor()
{
	
}

void ACSubjugate_Actor::BeginPlay()
{
	Super::BeginPlay();
	FVector pos = GetActorLocation();
	pos.Z = 20;
	SetActorLocation(pos);
}

void ACSubjugate_Actor::CastSubjugate()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Effect, GetActorLocation(), FRotator::ZeroRotator, true);
}

void ACSubjugate_Actor::Cast(float delay)
{
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([=]() 
	{
		FTransform transform;
		transform.SetLocation(GetActorLocation());
		FActorSpawnParameters param;
		param.Owner = this;

		if (!!MagicCircle)
		{
			AActor* circle = GetWorld()->SpawnActor<AActor>(MagicCircle, transform, param);
			circle->SetLifeSpan(CastTime);
		}

		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &ACSubjugate_Actor::CastSubjugate, CastTime, false);
	}), delay, false);
	
}