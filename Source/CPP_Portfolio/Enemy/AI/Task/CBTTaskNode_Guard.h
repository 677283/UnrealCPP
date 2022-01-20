#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Guard.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Guard : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Guard();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	float GetRandomGuardDirection();
};
