#include "CSlashProjectile.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ACSlashProjectile::ACSlashProjectile()
{
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Box);

	Projectile->ProjectileGravityScale = 0;

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACSlashProjectile::OnBoxBeginOverlap);
}

void ACSlashProjectile::BeginPlay()
{
	Super::BeginPlay();
	FRotator rotator = UKismetMathLibrary::RandomRotator(true);
	rotator.Pitch = 0;
	rotator.Yaw = 0;
	AddActorLocalRotation(rotator);
	SetLifeSpan(2);
}

void ACSlashProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (HitActors.Find(OtherActor))
		return;

}