#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CQuickSlotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCQuickSlotComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UCQuickSlotComponent();

private:
	UPROPERTY(EditDefaultsOnly)
		int32 MaxSlotCount;

protected:
	virtual void BeginPlay() override;

public:
	void RegisterSlot(int32 InIndex, UObject* InObject);
	void UseSlot(int32 InIndex);

private:
	TArray<UObject*> SlotList;
};
