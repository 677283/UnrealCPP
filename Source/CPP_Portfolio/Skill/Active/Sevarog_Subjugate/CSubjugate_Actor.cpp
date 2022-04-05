#include "CSubjugate_Actor.h"
#include "Global.h"

ACSubjugate_Actor::ACSubjugate_Actor()
{
	
}

void ACSubjugate_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	FTransform transform;
	transform.SetLocation(GetActorLocation());
	FActorSpawnParameters param;
	param.Owner = this;

	GetWorld()->SpawnActor<AActor>(MagicCircle, transform, param);

	FTimerHandle handle;
	GetWorldTimerManager().SetTimer(handle, this, &ACSubjugate_Actor::CastSubjugate, CastTime, false);
}

void ACSubjugate_Actor::CastSubjugate()
{
	UGameplayStatics::SpawnEmitterAttached(Effect, GetRootComponent(), "", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::KeepRelativeOffset);
}