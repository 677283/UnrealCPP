#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* DefaultHitMontage;

	UPROPERTY(EditDefaultsOnly)
		float DefaultHitMontagePlayRitio = 1;

protected:
	UPROPERTY(VisibleInstanceOnly)
		bool CanMove = true;
	
	UPROPERTY(EditDefaultsOnly)
		float RunSpeed = 800;

	UPROPERTY(EditDefaultsOnly)
		float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_Damage> DamageWidget;

public:
	ACCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	
};
