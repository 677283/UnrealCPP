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
	void AddSkill(class UCSkill* InSkill);
	class UCSkill* GetSkill(FName InSkillName);

private:
	TMap<FName, class UCSkill*> Skills;
		
};
