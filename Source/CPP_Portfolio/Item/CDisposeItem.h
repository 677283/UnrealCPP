#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDisposeItem.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACDisposeItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDisposeItem();
	
private:
	UPROPERTY(EditAnywhere)
		class UCItemAsset* Item;

protected:
	virtual void BeginPlay() override;

};
