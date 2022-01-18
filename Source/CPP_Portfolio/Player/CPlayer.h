#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "CPlayer.generated.h"

//BindAction 데이터 보내기용 델리게이트
//DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int);

UCLASS()
class CPP_PORTFOLIO_API ACPlayer : public ACCharacter , public IGenericTeamAgentInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class USceneCaptureComponent2D* Capture;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Widget")
		TSubclassOf<class UCWidget_PickUp> PickUpWidgetClass;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Widget")
		TSubclassOf<class UCWidget_OnRide> RideWidgetClass;

	UPROPERTY(EditDefaultsOnly, NoClear, Category = "Widget")
		TSubclassOf<class UCWidget_HUD> HUDClass;


	UPROPERTY(EditDefaultsOnly, Category = "BasicItem")
		FString BaiscWeaponName;

	UPROPERTY(EditAnywhere)
		float MouseSensitivity = 0.5;
	
	UPROPERTY(EditAnywhere)
		float AttackRotatorSpeed = 1;

	UPROPERTY(EditDefaultsOnly)
		class UNiagaraSystem* DashEffect;
	
	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 44;

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FGenericTeamId GetGenericTeamId() const override;

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
	void SkillTreeToggle();
	void EquipToggle();
	
	//void WidgetToggleSetting();
	void OnDebug();
	void OnRiding();
	void OnJump();
	void OnDash();

public:
	void SwapWeapon();
	void SwapWeaponNotify();
	void OnPickUpWidget(class UCItem* InItem);
	void OffPickUpWidget();
	void OnRideWidget(class ACHorse* InHorse);
	void OffRideWidget();
	
	FORCEINLINE class UCWidget_HUD* GetHUD() { return HUD; }
	FORCEINLINE void OffDash() { bDash = false; }
	FORCEINLINE void SetDash(class UCSkill* InDash) { DashSkill = InDash; }
	FORCEINLINE void SetCanMove(bool canMove) { bCanMove = canMove; }

private:
	class UCWidget_PickUp* PickUpWidget;
	class UCWidget_OnRide* RideWidget;
	class UCWidget_QuickSlot* QuickSlotWidget;
	class UCWidget_HUD* HUD;
	class UCharacterMovementComponent* Movement;

	class UCItem* CheckItem;
	class ACHorse* CheckHorse;

private:
	class UCSkill* DashSkill;
	class UAnimMontage* DashMontage;
	bool bCanMove=true;
	bool bDash;
};

