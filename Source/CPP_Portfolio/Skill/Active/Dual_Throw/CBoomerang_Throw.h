#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoomerang_Throw.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACBoomerang_Throw : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoomerang_Throw();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
