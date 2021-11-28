#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
#include "CPlayer.generated.h"

//BindAction 데이터 보내기용 델리게이트
//DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const int);

UCLASS()
class CPP_PORTFOLIO_API ACPlayer : public ACCharacter
{
	GENERATED_BODY()

#pragma region Components
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
		TSubclassOf<class UCWidget_Inventory> InventoryWidgetClass;

#pragma endregion

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
public:
	void OnPickUpWidget(class UCItemAsset* InItem);
	void OffPickUpWidget();
	

private:
	UPROPERTY(EditAnywhere)
		float MouseSensitivity = 0.5;
public:
	class UCSkill* Slash;
	TSubclassOf<UCSkill> SlashClass;
	class UCSkill* Throw;
	TSubclassOf<UCSkill> ThrowClass;

private:
	class UCWidget_PickUp* PickUpWidget;
	class UCWidget_Inventory* InventoryWidget;
	bool bPickUp = false;
	class UCItemAsset* CheckItem;
	bool bInvenToggle = true;

	class UInputComponent* Input;
};

