#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacterState.generated.h"

UINTERFACE(MinimalAPI)
class UICharacterState : public UInterface
{
	GENERATED_BODY()
};

class CPP_PORTFOLIO_API IICharacterState
{
	GENERATED_BODY()

public:
	virtual bool IsStateIdle() = 0;
	virtual void SetStateIdle() = 0;
	virtual bool IsStateAction() = 0;
	virtual void SetStateAction() = 0;
	virtual bool IsStateHitted() = 0;
	virtual void SetStateHitted() = 0;
};
