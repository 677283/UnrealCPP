#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Approach.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Approach : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_Approach();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
