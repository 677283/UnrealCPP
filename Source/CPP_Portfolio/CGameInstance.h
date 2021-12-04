#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCGameInstance();

private:
	UPROPERTY(EditDefaultsOnly)
		TMap<FString, class UCItemAsset*> ItemList;

public:
	class UCItem* CreateItem(class ACharacter* InOwner, FString InItemName);
};
