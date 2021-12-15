#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTestActor.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACTestActor : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UPoseableMeshComponent* Poseable;

	UPROPERTY(EditAnywhere)
		float Length = 50;

	UPROPERTY(EditAnywhere)
		FRotator Rotate;

	UPROPERTY(EditAnywhere)
		FRotator SubRotate;

	UPROPERTY(EditAnywhere)
		float Gap;

	UPROPERTY(EditAnywhere)
		FVector Direction;

public:	
	ACTestActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FVector RootDirection;
	TArray<FVector> Original;
	TArray<FName> AllName;
};
