#pragma once

#include "CoreMinimal.h"
#include "Item/CItemAsset.h"
#include "Item/CItemStructures.h"
#include "CEquipAsset.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCEquipAsset : public UCItemAsset
{
	GENERATED_BODY()
	
public:
	UCEquipAsset();

private:
	UPROPERTY(VisibleAnywhere, Category = "EquipInfo")
		EEquipType EquipType;

public:
	virtual class UCItem* CreateItem(class ACharacter* InOwner, class UCItem* InItem) override;

protected:
	FORCEINLINE void SetEquipType(EEquipType type) { EquipType = type; }

};
