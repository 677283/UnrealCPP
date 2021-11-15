#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CPushingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PORTFOLIO_API UCPushingComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UCPushingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	class ACharacter* OwnerCharacter;

private:
	UPROPERTY(EditAnywhere, Category = "Debug")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
	UPROPERTY(EditDefaultsOnly)
		float Radius = 35;
	UPROPERTY(EditDefaultsOnly)
		float PushingPower = 0.1;
};
