#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CItemStructures.h"
#include "CItemAsset.generated.h"

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCItemAsset : public UObject
{
	GENERATED_BODY()
	
public:
	UCItemAsset();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		FString Name;

	UPROPERTY(VisibleAnywhere, Category = "BaseInfo")
		EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		TSubclassOf<class ACDropActor> DropActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		class UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
		int32 MaxAmount;

public:
	virtual void BeginPlay(class ACharacter* InOwner);
	
public:
	virtual void DropItem(FVector InDropPosition);
	virtual void PickUpItem(class ACharacter* InOwner);


public:
	virtual void UseItem() {}
	virtual void DestroyItem();
	int32 AddAmount(int32 InAmount);

protected:
	FORCEINLINE void SetType(EItemType InType) { ItemType = InType; }
public:
	FORCEINLINE EItemType GetType() { return ItemType; }
	FORCEINLINE ACharacter* GetOwner() { return OwnerCharacter; }
	FORCEINLINE void SetAmount(int32 InAmount) { Amount = InAmount; }
	FORCEINLINE int32 GetAmount() { return Amount; }
	FORCEINLINE class UTexture2D* GetIcon() { return Icon; };
	FORCEINLINE FString GetItemName() { return Name; }

private:
	UFUNCTION()
		void OnDropActorBeginOverlap(class ACPlayer* InPlayer);
protected:
	class ACharacter* OwnerCharacter;
	class ACDropActor* DropActor;
	
private:
	int32 Amount = 1;
};
