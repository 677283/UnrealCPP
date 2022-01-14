#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_AI();

private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID;

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

};
