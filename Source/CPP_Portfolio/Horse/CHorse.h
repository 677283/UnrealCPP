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
};
