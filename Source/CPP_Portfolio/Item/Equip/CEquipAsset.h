#pragma once

#include "CoreMinimal.h"
#include "Item/CItemAsset.h"
#include "CEquipAsset.generated.h"

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	Weapon, Armor, Max,
};

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
	virtual void BeginPlay(class ACharacter* InOwner) override;

protected:
	FORCEINLINE void SetEquipType(EEquipType type) { EquipType = type; }

public:
	FORCEINLINE const EEquipType GetEquipType() { return EquipType; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
public:
	virtual void UseItem() override;

public:
	virtual void Equip();
	virtual void Unequip();

protected:
	bool bEquipping = false;
	bool Enabled;
};
