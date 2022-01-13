#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");

}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

