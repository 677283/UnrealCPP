//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "CBehaviorComponent.generated.h"
//
//UENUM(BlueprintType)
//enum class EBehaviorType : uint8
//{
//	Wait, Approach, Action, Patrol, Hitted, Avoid,
//};
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBehaviorTypeChanged, EBehaviorType, InPrevType, EBehaviorType, InNewType);
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class CPP_PORTFOLIO_API UCBehaviorComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:	
//	UCBehaviorComponent();
//
//private:
//	UPROPERTY(EditAnywhere)
//		FName BehaviorKey = "Behavior";
//
//	UPROPERTY(EditAnywhere)
//		FName PlayerKey = "Player";
//
//public:
//	UFUNCTION(BlueprintPure)
//		bool IsWaitMode();
//
//	UFUNCTION(BlueprintPure)
//		bool IsApproachv();
//
//	UFUNCTION(BlueprintPure)
//		bool IsActionMode();
//
//	UFUNCTION(BlueprintPure)
//		bool IsPatrolMode();
//
//	UFUNCTION(BlueprintPure)
//		bool IsHittedMode();
//
//	UFUNCTION(BlueprintPure)
//		bool IsAvoidMode();
//
//	FORCEINLINE void SetBlackboard(class UBlackboardComponent* InBlackboard) { Blackboard = InBlackboard; }
//
//public:
//	void SetWaitMode();
//	void SetApproachv();
//	void SetActionMode();
//	void SetPatrolMode();
//	void SetHittedMode();
//	void SetAvoidMode();
//
//	class ACharacter* GetTargetCharacter();
//
//protected:
//	virtual void BeginPlay() override;
//
//private:
//	void ChangeType(EBehaviorType InType);
//	EBehaviorType GetType();
//
//public:
//	UPROPERTY(BlueprintAssignable)
//		FBehaviorTypeChanged OnBehaviorTypeChanged;
//
//private:
//	class UBlackboardComponent* Blackboard;
//};
