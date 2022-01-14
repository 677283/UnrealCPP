#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACAIController();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UAIPerceptionComponent* Perception;

	UPROPERTY(VisibleDefaultsOnly)
		class UCBehaviorComponent* Behavior;

	UPROPERTY(EditDefaultsOnly)
		float MeleeActionRange = 150;

	UPROPERTY(EditAnywhere)
		bool bDrawDebug;

	UPROPERTY(EditAnywhere)
		float AdjustCircleHeight = 50;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

public:
	float GetSightRadius();

private:
	UFUNCTION()
		void OnPerceptionUpdate(const TArray<AActor*>& UpdateActors);

public:
	FORCEINLINE float GetMeleeActionRange() { return MeleeActionRange; }

private:
	class ACEnemy_AI* OwnerEnemy;
	class UAISenseConfig_Sight* Sight;

};
