#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSlashProjectile.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACSlashProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSlashProjectile();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	TArray<class AActor*> HitActors;
};
