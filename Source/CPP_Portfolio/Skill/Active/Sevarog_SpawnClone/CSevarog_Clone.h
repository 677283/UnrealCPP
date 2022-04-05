#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CSevarog_Clone.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACSevarog_Clone : public ACharacter
{
	GENERATED_BODY()

public:
	ACSevarog_Clone();

private:
	UPROPERTY(EditDefaultsOnly)
		float LifeTime;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* SpawnParticle;
	
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* DestroyParticle;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montage;

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

public:
	void DestroyClone();

};
