#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnEquipActorBeginOverlap, class ACharacter*, InAttacker, class AActor*, InAttackCauser, class ACharacter*, InOtherCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipActorCollision);
	
UCLASS()
class CPP_PORTFOLIO_API ACEquipActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipActor();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		virtual void AttachTo(FName InSocketName);

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnEquipmentToggleHands(FName InSocketName);

	virtual void OnCollision();
	virtual void OffCollision();
	virtual void SetVisibility(bool InBool);
	virtual void SetOwnerCharacter(class ACharacter* InOwner);

	UFUNCTION()
		virtual void Equip();
	UFUNCTION()
		virtual void Unequip();


private:
	TArray<class UShapeComponent*> Collisions;
	TArray<class AActor *> HittedActors;

protected:
	class ACharacter* OwnerCharacter;

public:
	FOnEquipActorBeginOverlap OnEquipActorBeginOverlap;
	FEquipActorCollision OnEquipActorCollision;
	FEquipActorCollision OffEquipActorCollision;
};
