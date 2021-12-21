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
	class UCSkill* GetSkill(TSubclassOf<class UCSkill> InSkillClass);

	int32 LevelCheck(TSubclassOf<class UCSkill> InSkillClass);
	void SkillLevelUp(TSubclassOf<class UCSkill> InSkillClass);

	FORCEINLINE int32 GetSkillPoint() { return SkillPoint; }
private:
	UPROPERTY()
	TMap<FName, class UCSkill*> Skills;
	int32 SkillPoint = 3;

};
