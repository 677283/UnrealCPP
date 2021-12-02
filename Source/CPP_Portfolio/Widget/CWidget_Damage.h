#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_Damage.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_Damage : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly)
		float SpawnLife;
	UPROPERTY(EditDefaultsOnly)
		float ZPower = 1;



	UPROPERTY(EditDefaultsOnly)
		float Jump = 100;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetWorldPos(FVector InPosition);

private:
	FVector WorldPosition;
	float ZValue = 0.5;
};
