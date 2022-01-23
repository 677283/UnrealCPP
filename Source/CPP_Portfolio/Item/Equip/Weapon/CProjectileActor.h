#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectileActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnProjectileBeginOverlap, class UPrimitiveComponent*, OverlappedComponent, class AActor*, OtherActor, class UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);

UCLASS()
class CPP_PORTFOLIO_API ACProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectileActor();

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;
	
private:
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FOnProjectileBeginOverlap OnProjectileBeginOverlap;
};
