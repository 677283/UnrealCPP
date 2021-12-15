#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CPlayer.generated.h"

//BindAction 데이터 보내기용 델리게이트
//DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int);

UCLASS()
class CPP_PORTFOLIO_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly)
		class UCSkillComponent* Skill;

	UPROPERTY(VisibleDefaultsOnly)
		class UCInventoryComponent* Inventory;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_PickUp> PickUpWidgetClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_OnRide> RideWidgetClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCWidget_Inventory> InventoryWidgetClass;

	UPROPERTY(EditAnywhere)
		float MouseSensitivity = 0.5;
	
	UPROPERTY(EditAnywhere)
		float RotatorSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCSkill> BowUltimateClass;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float AxisValue);
	void OnMoveRight(float AxisValue);
	void OnHorizontalLook(float AxisValue);
	void OnVerticalLook(float AxisValue);
	
	void Sprint_Pressed();
	void Sprint_Released();

	void Equip_Weapon();
	void BasicAttack(FKey InKey);
	void Skill_1();
	void Skill_2();
	void PickUp();
	void InventoryToggle();
	void OnDebug();
	void OnRiding();
	void OnJump();

public:
	void OnPickUpWidget(class UCItem* InItem);
	void OffPickUpWidget();
	void OnRideWidget(class ACHorse* InHorse);
	void OffRideWidget();
	
public:
	UPROPERTY()
	class UCSkill* Slash;
	TSubclassOf<UCSkill> SlashClass;
	UPROPERTY()
	class UCSkill* Throw;
	TSubclassOf<UCSkill> ThrowClass;
	UPROPERTY()
	class UCSkill* BowUltimate;
private:
	class UCWidget_PickUp* PickUpWidget;
	class UCWidget_Inventory* InventoryWidget;
	class UCWidget_OnRide* RideWidget;
	class UCharacterMovementComponent* Movement;

	bool bPickUp = false;
	class UCItem* CheckItem;
	class ACHorse* CheckHorse;
};

