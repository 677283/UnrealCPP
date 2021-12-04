#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCInventoryComponent();


private:
	UPROPERTY(EditAnywhere)
		int32 InventorySize;

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE class UTexture2D* GetIcon(int32 InIndex) { return Inventory[InIndex] ? Inventory[InIndex]->GetIcon() : nullptr; }

public:
	bool AddItem(class UCItem* InItem);
	void UseItem(int32 InIndex);
	void SwapItem(int32 InIndex_1, int32 InIndex_2);

public:
	UFUNCTION()
		void OnEquip(class UCItem* InItem);
	UFUNCTION()
		void OnUnequip(class UCItem* InItem);

private:
	int32 CheckSlot(class UCItem* InItem);
private:
	TArray<class UCItem*> Inventory;
	class ACharacter* OwnerCharacter;
public:
	FOnAddItem OnInventoryUpdate;
};
