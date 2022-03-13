#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Boss.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTService_Boss : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_Boss();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
