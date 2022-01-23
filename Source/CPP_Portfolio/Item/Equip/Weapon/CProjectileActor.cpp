#include "CProjectileActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACProjectileActor::ACProjectileActor()
{
	USceneComponent* root;

	CHelpers::CreateComponent<USceneComponent>(this, &root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", root);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");
}

void ACProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<UShapeComponent*> collisions;

	GetComponents(collisions);

	for (UShapeComponent* collision : collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACProjectileActor::OnComponentBeginOverlap);
	}
}

void ACProjectileActor::OnComponentBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OnProjectileBeginOverlap.IsBound())
		OnProjectileBeginOverlap.Broadcast(OverlappedComponent, OtherActor,  OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
