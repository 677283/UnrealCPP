#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/CItem.h"
#include "CInventoryComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnAddItem, int32, UObject*);
DECLARE_DELEGATE_OneParam(FInventoryOnEquip, class UCEquipItem*);
DECLARE_DELEGATE_TwoParams(FOnSlotUpdate, int32, class UCItem*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInventoryComponent();

private:
	UPROPERTY(EditAnywhere, meta = (ClampMax = 40.00, ClampMin = 1.00))
		int32 InventorySize;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class UTexture2D* GetIcon(int32 InIndex) { return Inventory[InIndex] ? Inventory[InIndex]->GetIcon() : nullptr; }

public:
	bool AddItem(class UCItem* InItem);
	bool AddItem(int32 InIndex, class UCItem* InItem);
	void UseItem(int32 InIndex);
	void UseItem(class UCItem* InItem);
	void SwapItem(int32 InIndex_1, int32 InIndex_2);
	

public:
	void OnEquip(class UCItem* InEquipItem, class UCItem* InUnequipItem);
	bool OnUnequip(class UCItem* InUnequipItem);

	void OnUpdateItem(class UCItem* InItem);
	void OnDestroyItem(class UCItem* InItem);


private:
	int32 CheckSlot(class UCItem* InItem);

private:
	TArray<class UCItem*> Inventory;
	TArray<FDelegateHandle> UpdateDelegateHandles;
	TArray<FDelegateHandle> DestroyDelegateHandles;
	class ACharacter* OwnerCharacter;

public:
	FOnAddItem OnAddItem;
	FInventoryOnEquip OnEquipInventory;
	FOnSlotUpdate OnSlotUpdate;
};
