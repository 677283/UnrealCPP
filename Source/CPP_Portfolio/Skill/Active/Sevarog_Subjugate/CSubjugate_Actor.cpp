#include "CSubjugate_Actor.h"
#include "Global.h"

ACSubjugate_Actor::ACSubjugate_Actor()
{
	
}

void ACSubjugate_Actor::BeginPlay()
{
	Super::BeginPlay();


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
			GetWorld()->SpawnActor<AActor>(MagicCircle, transform, param);

		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &ACSubjugate_Actor::CastSubjugate, CastTime, false);
	}), delay, false);
	
}