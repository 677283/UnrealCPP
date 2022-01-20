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
		FString WeaponName;

	UPROPERTY(EditDefaultsOnly)
		float AttackRange = 50;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = ENEMY_BASIC_TEAMID;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void Attack();
public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE bool CanAttack() { return bCanAttack; }
	FORCEINLINE float GetAttackRange() { return AttackRange; }

private:
	bool bCanAttack = true;
	class UCWeaponItem* Weapon;
};
