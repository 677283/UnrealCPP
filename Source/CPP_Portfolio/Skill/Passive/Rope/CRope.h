#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRope.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACRope : public AActor
{
	GENERATED_BODY()
	
public:	
	ACRope();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetTargetPosition(FVector position);
	void OnParticle();
	void OffParticle();

private:
	FVector Target;
	float Power = 0;

};
