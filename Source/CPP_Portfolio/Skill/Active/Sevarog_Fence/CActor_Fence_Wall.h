#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActor_Fence_Wall.generated.h"

DECLARE_DELEGATE(FDelegate_ReadyWall);

UCLASS()
class CPP_PORTFOLIO_API ACActor_Fence_Wall : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActor_Fence_Wall();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float UpSpeed;

public:
	FDelegate_ReadyWall OnReadyWall;

};
