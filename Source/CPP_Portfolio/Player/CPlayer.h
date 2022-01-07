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
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
		class UCInventoryComponent* Inventory;

	UPROPERTY(VisibleDefaultsOnly)
		class UCQuickSlotComponent* QuickSlot;

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
	void SkillTreeToggle();
	void EquipToggle();
	
	void WidgetToggleSetting();
	void OnDebug();
	void OnRiding();
	void OnJump();

public:
	void OnPickUpWidget(class UCItem* InItem);
	void OffPickUpWidget();
	void OnRideWidget(class ACHorse* InHorse);
	void OffRideWidget();
	
	FORCEINLINE class UCWidget_HUD* GetHUD() { return HUD; }

private:
	class UCWidget_PickUp* PickUpWidget;
	class UCWidget_OnRide* RideWidget;
	class UCWidget_QuickSlot* QuickSlotWidget;
	class UCWidget_HUD* HUD;
	class UCharacterMovementComponent* Movement;

	class UCItem* CheckItem;
	class ACHorse* CheckHorse;

};

