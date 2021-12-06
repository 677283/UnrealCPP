#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CRidingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCRidingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCRidingComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnRide(class ACHorse* InHorse);
	void OffRide();
	bool IsRiding();

	FORCEINLINE class ACHorse* GetRidingHorse() { return RidingHorse; }

private:
	class ACHorse* RidingHorse;

	TArray<class UShapeComponent*> Collisions;
	TArray<TEnumAsByte<ECollisionEnabled::Type>> CollisionEnableds;
};
