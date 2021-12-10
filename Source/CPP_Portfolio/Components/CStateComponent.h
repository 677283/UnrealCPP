#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Equip, Action, Skill, Hitted, Dead, Mount, Max,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE void SetStateIdle() { State = EStateType::Idle; }
	FORCEINLINE void SetStateEquip() { State = EStateType::Equip;  }
	FORCEINLINE void SetStateAction() { State = EStateType::Action;  }
	FORCEINLINE void SetStateSkill() { State = EStateType::Skill;  }
	FORCEINLINE void SetStateHitted() { State = EStateType::Hitted; }
	FORCEINLINE void SetStateDead() { State = EStateType::Dead; }
	FORCEINLINE void SetStateMount() { State = EStateType::Mount; }

	FORCEINLINE bool IsStateIdle() { return State == EStateType::Idle; }
	FORCEINLINE bool IsStateEquip() { return State == EStateType::Equip; }
	FORCEINLINE bool IsStateAction() { return State == EStateType::Action; }
	FORCEINLINE bool IsStateSkill() { return State == EStateType::Skill; }
	FORCEINLINE bool IsStateHitted() { return State == EStateType::Hitted; }
	FORCEINLINE bool IsStateDead() { return State == EStateType::Dead; }
	FORCEINLINE bool IsStateMount() { return State == EStateType::Mount; }
	FORCEINLINE EStateType GetState() { return State; }
private:
	EStateType State;
};
