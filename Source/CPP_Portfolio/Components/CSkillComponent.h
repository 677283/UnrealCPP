#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCSkillComponent();

protected:
	virtual void BeginPlay() override;

public:
	void AddSkill(class CSkill* InSkill);

private:
	TMap<FName, class UCSkill*> Skills;
		
};
