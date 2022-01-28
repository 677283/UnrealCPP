#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Item/CItemStructures.h"
#include "CParryingComponent.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCParryingComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UCParryingComponent();

	UPROPERTY(EditDefaultsOnly)
		FCustomDamageEvent DamageEvent;

protected:
	virtual void BeginPlay() override;

private:
	void DoParry();

};
