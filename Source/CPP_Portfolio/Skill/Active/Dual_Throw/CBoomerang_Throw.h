#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoomerang_Throw.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrowBeginOverlap, class AActor*, OtherActor);

UCLASS()
class CPP_PORTFOLIO_API ACBoomerang_Throw : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoomerang_Throw();

private:
	UPROPERTY(EditDefaultsOnly)
		float RotateSpeed = 1600;

	UPROPERTY(EditDefaultsOnly)
		float ProjectileVelocity = 1000;

	UPROPERTY(EditDefaultsOnly)
		float InterpSpeedMax = 10;

	UPROPERTY(EditDefaultsOnly)
		float InterpUpdateSpeed = 1;

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetBoomerang(class UCSkill* InSkill, class AActor* InWeapon, int32 InDirection);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


private:
	class UCSkill* Skill;
	class AActor* Weapon;
	TArray<class UShapeComponent*> Comps;
	int32 Direction;
	float InterpSpeed = 0;
private:
	FThrowBeginOverlap OnThrowBeginOverlap;
};
