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

protected:
	class ACharacter* OwnerCharacter;

	FString Name;
	class ACDropActor* DropActor;
	EItemType ItemType;
	class UTexture2D* Icon;

	int32 MaxAmount;
	int32 Amount = 1;
};
