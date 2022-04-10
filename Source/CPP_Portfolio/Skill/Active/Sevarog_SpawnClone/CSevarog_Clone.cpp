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
	
	if (!!SpawnParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SpawnParticle, GetActorLocation(), FRotator(), true);
	if (!!Montage)
		GetMesh()->PlayAnimation(Montage, false);
	SpawnDefaultController();
}

void ACSevarog_Clone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//FVector pos = GetActorLocation();
	//pos += GetActorForwardVector() * 300 * DeltaTime;
	//SetActorLocation(pos);
	AddMovementInput(GetActorForwardVector());
}

void ACSevarog_Clone::DestroyClone()
{
	if (!!DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation(), FRotator(), true);
	Destroy();
}

