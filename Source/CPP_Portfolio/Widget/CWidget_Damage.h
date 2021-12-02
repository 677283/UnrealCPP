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
		float YOffsetSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
		float XOffsetSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
		float YHeight = 100;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetWorldPos(FVector InPosition, FString InDamage);

private:
	FVector WorldPosition;
	class UTextBlock* Text;
	FString Damage;
	float StackSpawnLife=0;

	float YOffset = 0;
	float XOffset = 0;
};
