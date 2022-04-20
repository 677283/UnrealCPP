#include "CSubjugate_Actor.h"
#include "Global.h"
#include "particles/ParticleSystemComponent.h"

ACSubjugate_Actor::ACSubjugate_Actor()
{
	
}

void ACSubjugate_Actor::BeginPlay()
{
	Super::BeginPlay();


}

void ACSubjugate_Actor::CastSubjugate()
{
	FVector pos = GetActorLocation();
	UParticleSystemComponent* particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Effect, pos, FRotator(90,0,0), true);

	particle->OnParticleSpawn.AddDynamic(this, &ACSubjugate_Actor::Test);
}

void ACSubjugate_Actor::Cast(float delay)
{
	FTimerHandle handle;
	if (FMath::IsNearlyZero(delay))
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

		GetWorldTimerManager().SetTimer(handle, this, &ACSubjugate_Actor::CastSubjugate, CastTime, false);
		return;
	}

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

void ACSubjugate_Actor::Test(FName EventName, float EmitterTime, FVector Location, FVector Velocity)
{
	if (EventName == "SpawnTest")
		CLog::Log(EmitterTime);
}