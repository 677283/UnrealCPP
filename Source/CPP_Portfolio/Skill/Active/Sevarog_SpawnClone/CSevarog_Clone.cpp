#include "CSevarog_Clone.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"

ACSevarog_Clone::ACSevarog_Clone()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACSevarog_Clone::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeTime);
	if (!!AttachParticle)
		UGameplayStatics::SpawnEmitterAttached(AttachParticle, RootComponent, "", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset);
	if (!!SpawnParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, GetActorLocation(), FRotator::ZeroRotator, true);
	if (!!Montage)
		GetMesh()->PlayAnimation(Montage, false);
	SpawnDefaultController();
}

void ACSevarog_Clone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!!DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation(), FRotator::ZeroRotator, true);
}

void ACSevarog_Clone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddMovementInput(GetActorForwardVector());
}


