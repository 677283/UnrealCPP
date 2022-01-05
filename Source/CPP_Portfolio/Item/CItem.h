#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItemStructures.h"
#include "Interfaces/ISlotWidget.h"
#include "CItem.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateItem, UCItem*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDestroyItem, UCItem*);

UCLASS()
class CPP_PORTFOLIO_API UCItem : public UObject, public IISlotWidget
{
	GENERATED_BODY()
public:
	UCItem();

public:
	void InitializeItem(FString InName, class ACDropActor* InDrop, EItemType InType, class UTexture2D* InIcon, int32 InMaxAmount);
	
	virtual void UseItem();
	virtual void DestroyItem();

	virtual void DropItem(FVector InDropPosition);
	virtual void PickUpItem(class ACharacter* InOwner);
	
	int32 AddAmount(int32 InAmount);

public:
	FORCEINLINE ACharacter* GetOwner() { return OwnerCharacter; }
	FORCEINLINE void SetAmount(int32 InAmount) { Amount = InAmount; }
	FORCEINLINE int32 GetAmount() { return Amount; }
	FORCEINLINE virtual class UTexture2D* GetIcon() override { return Icon; };
	FORCEINLINE virtual void ActiveSlot() override { UseItem(); }
	FORCEINLINE FString GetItemName() { return Name; }
	FORCEINLINE EItemType GetItemType() { return ItemType; }

public:
	UFUNCTION()
		void OnDropActorBeginOverlap(class ACPlayer* InPlayer);

protected:
	class ACharacter* OwnerCharacter;
	FString Name;
	class ACDropActor* DropActor;
	EItemType ItemType;
	UPROPERTY()
		class UTexture2D* Icon;

	int32 MaxAmount;
	int32 Amount = 1;

public:
	FOnUpdateItem OnUpdateItem;
	FOnDestroyItem OnDestroyItem;
};
