#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CDisposeItem.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACDisposeItem : public ACharacter
{
	GENERATED_BODY()

public:
	ACDisposeItem();

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCItemAsset> ItemClass;

protected:
	virtual void BeginPlay() override;

};
