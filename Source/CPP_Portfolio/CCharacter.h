#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ICharacterState.h"
#include "CCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Idle = 0, Action, Skill, Hitted, Max,
};

UCLASS()
class CPP_PORTFOLIO_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCPushingComponent* Pushing;
protected:
	UPROPERTY(VisibleDefaultsOnly)
		class UCEquipComponent* Equip;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

public:
	ACCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
		float Health = MaxHealth;
	
	UPROPERTY(VisibleInstanceOnly)
		bool CanMove = true;
protected:
	UPROPERTY(EditDefaultsOnly)
		float RunSpeed = 800;

	UPROPERTY(EditDefaultsOnly)
		float WalkSpeed = 200;

};
