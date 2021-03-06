#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CItemStructures.h"
#include "CItemAsset.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCItemAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCItemAsset();

private:
	UPROPERTY(EditDefaultsOnly, NoClear, Category = "BaseInfo")
		FString Name;

	UPROPERTY(VisibleAnywhere, Category = "BaseInfo")
		EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		TSubclassOf<class ACDropActor> DropActorClass;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "BaseInfo")
		class UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, NoClear, meta = (ClampMin = 1.00))
		int32 MaxAmount = 1;

public:
	virtual class UCItem* CreateItem(class ACharacter* InOwner, class UCItem* InItem);

protected:
	FORCEINLINE void SetType(EItemType InType) { ItemType = InType; }

protected:
	UPROPERTY()
	TArray<class UCItem*> ItemList;
};
