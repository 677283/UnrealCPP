#pragma once

#include "CoreMinimal.h"
#include "Item/CItem.h"
#include "Item/CItemStructures.h"
#include "CEquipItem.generated.h"

DECLARE_DELEGATE_OneParam(FOnEquipItem, UCEquipItem*);

UCLASS()
class CPP_PORTFOLIO_API UCEquipItem : public UCItem
{
	GENERATED_BODY()
	
public:
	UCEquipItem();

public:
	void InitializeEquipItem(EEquipType InEquipType);

	virtual void UseItem() override;
	virtual void Equip();
	virtual void Unequip();

public:
	FORCEINLINE const EEquipType GetEquipType() { return EquipType; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }

protected:
	FORCEINLINE void SetEquipType(EEquipType type) { EquipType = type; }

private:
	EEquipType EquipType;

protected:
	bool bEquipping;

public:
	FOnEquipItem OnEquipItem;
};
