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
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

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
private:
	FThrowBeginOverlap OnThrowBeginOverlap;
};
