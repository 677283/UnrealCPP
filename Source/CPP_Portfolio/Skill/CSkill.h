#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/ISlotWidget.h"
#include "CSkill.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnCooldown);

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Passive, Active, Max,
};


UCLASS(Blueprintable)
class CPP_PORTFOLIO_API UCSkill : public UObject, public IISlotWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		FName Name;

	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly)
		float Cooldown;

	UPROPERTY(VisibleDefaultsOnly)
		ESkillType Type = ESkillType::Max;

public:
	virtual void BeginPlay(class ACharacter* InOwner);

	virtual void DoSkill();
	virtual void BeginDoSkill() {};
	virtual void EndDoSkill() {};

	FORCEINLINE FName GetSkillName() { return Name; }
	FORCEINLINE int32 GetSkillLevel() { return SkillLevel; }
	FORCEINLINE void SkillLevelUp() { SkillLevel++; }
	FORCEINLINE class UTexture2D* GetIcon() override { return Icon; }
	FORCEINLINE virtual void ActiveSlot() override { DoSkill(); }

protected:
	void SetSkillType(ESkillType InSkillType) { Type = InSkillType; }
	void CooldownTick();

protected:
	class ACharacter* OwnerCharacter;
	int32 SkillLevel = 0;
	FTimerHandle CooldownHandle;
	float CooldownStack;

	FOnCooldown OnCooldown;
};
