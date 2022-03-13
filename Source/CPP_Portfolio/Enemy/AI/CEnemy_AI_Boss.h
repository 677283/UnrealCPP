#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/CEnemy_AI.h"
#include "CEnemy_AI_Boss.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACEnemy_AI_Boss : public ACEnemy_AI
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* AttackMontage;
public:
	void Boss_Attack();
};
