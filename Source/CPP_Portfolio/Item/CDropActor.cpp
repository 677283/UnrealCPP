#include "CDropActor.h"
#include "Global.h"
#include "Components/ShapeComponent.h"

ACDropActor::ACDropActor()
{
	PrimaryActorTick.bCanEverTick = true;

	
}

void ACDropActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collision = CHelpers::GetComponent<UShapeComponent>(this);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACDropActor::OnComponentBeginOverlap);
}

void ACDropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0, RotateSpeed * DeltaTime, 0));
}

void ACDropActor::Drop()
{
	Mesh->SetVisibility(true);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);
}

void ACDropActor::PickUp()
{
	Mesh->SetVisibility(false);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
}

void ACDropActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}