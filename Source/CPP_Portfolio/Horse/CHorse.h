#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CHorse.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACHorse : public ACharacter
{
	GENERATED_BODY()

public:
	ACHorse();

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCPushingComponent* Pushing;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* BrakeMontage;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);
	void OnHorizontalLook(float AxisValue);
	void OnVerticalLook(float AxisValue);

	void OffRiding();

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE void SetRider(class ACCharacter* InRider) { Rider = InRider; }
	FORCEINLINE void FinishBrake() { bBrake = false; }

private:
	class ACCharacter* Rider;
	bool bMoveForward;
	bool bMoveRight;
	bool bBrake;
};
