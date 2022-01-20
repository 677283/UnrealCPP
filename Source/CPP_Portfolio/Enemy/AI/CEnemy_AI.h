#pragma once

#include "CoreMinimal.h"
#include "Enemy/CEnemy.h"
#include "CEnemy_AI.generated.h"

#define ENEMY_BASIC_TEAMID 4;

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
		uint8 TeamID = ENEMY_BASIC_TEAMID;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE bool CanAttack() { return bCanAttack; }

private:
	bool bCanAttack = true;
};
