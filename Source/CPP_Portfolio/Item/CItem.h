#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CItemStructures.h"
#include "CItem.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCItem : public UObject
{
	GENERATED_BODY()
public:
	UCItem();

public:
	virtual void BeginPlay(class ACharacter* InOwner);

	virtual void UseItem() {}
	virtual void DestroyItem() {};

	int32 AddAmount(int32 InAmount) { return Amount; };
	
public:
	FORCEINLINE ACharacter* GetOwner() { return OwnerCharacter; }
	FORCEINLINE void SetAmount(int32 InAmount) { Amount = InAmount; }
	FORCEINLINE int32 GetAmount() { return Amount; }
	FORCEINLINE class UTexture2D* GetIcon() { return Icon; };
	FORCEINLINE FString GetItemName() { return Name; }

protected:
	class ACharacter* OwnerCharacter;

	FString Name;
	class ACDropActor* DropActor;
	EItemType ItemType;
	UPROPERTY()
		class UTexture2D* Icon;

	int32 MaxAmount;
	int32 Amount = 1;
};
