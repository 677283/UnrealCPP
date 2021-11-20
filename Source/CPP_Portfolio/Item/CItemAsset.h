#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CItemAsset.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	None, Equip, Consumable, ETC, Max,
};

UCLASS()
class CPP_PORTFOLIO_API UCItemAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UCItemAsset();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		FName Name;

	UPROPERTY(VisibleAnywhere, Category = "BaseInfo")
		EItemType ItemType;

	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		AActor* DropActor;

	UPROPERTY(EditDefaultsOnly, Category = "BaseInfo")
		class UTexture2D* Icon;

public:
	virtual void BeginPlay(class ACharacter* InOwner);

protected:
	FORCEINLINE void SetType(EItemType InType) { ItemType = InType; }
	FORCEINLINE EItemType GetType() { return ItemType; }

public:
	virtual void UseItem() {};
	FORCEINLINE void SellItem() {};
	FORCEINLINE void BuyItem() {};

protected:
	class ACharacter* OwnerCharacter;
};
