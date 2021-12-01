#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDropActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDropActorBeginOverlap, class ACPlayer*, InPlayer);

UCLASS()
class CPP_PORTFOLIO_API ACDropActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDropActor();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(EditDefaultsOnly)
		FVector DropOffset;

	UPROPERTY(EditDefaultsOnly)
		float RotateSpeed = 0;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void Drop(FVector InDropPosition);
	void PickUp();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	class UShapeComponent* Collision;
	TArray<class UMeshComponent*> Meshes;

public:
	FOnDropActorBeginOverlap OnDropActorBeginOverlap;
};
