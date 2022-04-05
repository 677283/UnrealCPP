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
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
		FString WeaponName;

	UPROPERTY(EditDefaultsOnly)
		float AttackRange = 50;
	
	UPROPERTY(EditDefaultsOnly)
		float GuardRangeMax = 500;

	UPROPERTY(EditDefaultsOnly)
		float GuardRangeMin = 300;

	UPROPERTY(EditDefaultsOnly)
		float AttackDelay = 5;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	void EquipWeapon();
	void UnequipWeapon();
	void LeftAttack();
public:
	FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
	//FORCEINLINE uint8 GetTeamID() { return TeamID; }
	FORCEINLINE bool CanAttack() { return bCanAttack; }
	FORCEINLINE float GetAttackRange() { return AttackRange; }
	FORCEINLINE float GetGuardRangeMax() { return GuardRangeMax; }
	FORCEINLINE float GetGuardRangeMin() { return GuardRangeMin; }

protected:
	class UCWeaponItem* Weapon;
private:
	bool bCanAttack = true;
	float RemineTime = 0;
	float StackAttackTime = 0;
	int32 MaxAttackCnt = 2;
};
