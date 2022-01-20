#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CEnemy.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACEnemy : public ACCharacter
{
	GENERATED_BODY()
	
public:
	ACEnemy();

public:
	void Attack();
};
