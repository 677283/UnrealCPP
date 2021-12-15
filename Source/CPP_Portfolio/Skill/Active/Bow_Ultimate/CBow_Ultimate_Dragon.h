#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBow_Ultimate_Dragon.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACBow_Ultimate_Dragon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBow_Ultimate_Dragon();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleDefaultsOnly)
		class UPoseableMeshComponent* Mesh_1;

	UPROPERTY(VisibleDefaultsOnly)
		class UPoseableMeshComponent* Mesh_2;

	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
		FVector Direction = FVector(0, 0, 1);

	UPROPERTY(EditDefaultsOnly)
		float Radius = 50;

	UPROPERTY(EditDefaultsOnly)
		FRotator HeadRotate = FRotator(2, 0, 0);

	UPROPERTY(EditDefaultsOnly)
		FRotator BodyRotate = FRotator(-30, 0, 0);

	UPROPERTY(EditDefaultsOnly)
		float BodyGap = 25;

	UPROPERTY(EditDefaultsOnly)
		float Stretch = 10;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	TArray<FName> BoneAllName;
	FVector BodyScale = FVector(1, 1, 1);
	float SubScale;
	float SubScale_;
	float StretchGap = 0;
};
