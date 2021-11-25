#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInventoryComponent();


private:
	UPROPERTY(EditDefaultsOnly)
		int32 InventorySize;

protected:
	virtual void BeginPlay() override;


public:
	void AddItem(class UCItemAsset* InItem);
	void UseItem(int32 InIndex);
private:
	TArray<class UCItemAsset*> Inventory;
};
