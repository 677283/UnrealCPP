#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Fence.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_Fence : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_Fence();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
