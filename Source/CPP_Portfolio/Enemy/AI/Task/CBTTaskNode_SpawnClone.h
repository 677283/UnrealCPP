#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_SpawnClone.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCBTTaskNode_SpawnClone : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_SpawnClone();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
