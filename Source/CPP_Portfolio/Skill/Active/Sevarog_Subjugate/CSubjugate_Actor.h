#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSubjugate_Actor.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACSubjugate_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSubjugate_Actor();

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> MagicCircle;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Effect;

	UPROPERTY(EditDefaultsOnly)
		float CastTime = 1.0f;

private:
	void CastSubjugate();

protected:
	virtual void BeginPlay() override;

public:
	void Cast(float delay);

private:
	UFUNCTION()
	void Test(FName EventName, float EmitterTime, FVector Location, FVector Velocity);
};
