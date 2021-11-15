#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSkill.generated.h"

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Passive, Active, Max,
};

UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCSkill : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		float Cooldown;
	UPROPERTY(EditDefaultsOnly)
		FName Name;
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Icon;
	UPROPERTY(VisibleDefaultsOnly)
		ESkillType Type = ESkillType::Max;

public:
	virtual void BeginPlay(class ACharacter* InOwner);

	virtual void DoSkill() {};
	virtual void BeginDoSkill() {};
	virtual void EndDoSkill() {};

protected:
	void SetSkillType(ESkillType InSkillType) { Type = InSkillType; }

protected:
	class ACharacter* OwnerCharacter;
	int32 SkillLevel;
};
