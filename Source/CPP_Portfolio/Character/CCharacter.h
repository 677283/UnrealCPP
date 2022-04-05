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
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCPushingComponent* Pushing;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCRidingComponent* Riding;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCStatusComponent* Status;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCEquipComponent* Equip;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCSkillComponent* Skill;

	UPROPERTY(EditDefaultsOnly)
		TMap<int32, class UAnimMontage*> HitMontages;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* BrakeMontage;
	
	UPROPERTY(EditDefaultsOnly)
		int32 EndureLevel;

	UPROPERTY(EditDefaultsOnly)
		float EndureTime;

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 44;

	UPROPERTY(VisibleInstanceOnly)
		bool CanMove = true;
	
	UPROPERTY(EditDefaultsOnly)
		float RunSpeed = 800;

	UPROPERTY(EditDefaultsOnly)
		float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly)
		float SecondJumpPower = 700;

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

	void PlayBrakeMontage();

	virtual void Landed(const FHitResult& Hit) override;

public:
	FORCEINLINE bool IsSecondJump() { return bSecondJump; }
	FORCEINLINE uint8 GetTeamID() { return TeamID; }

protected:
	bool bSecondJump;
	float EndureGauge;
};
