#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "CGameInstance.h"

ACEnemy_AI::ACEnemy_AI()
{

}


void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

	Weapon = Cast<UCWeaponItem>(Cast<UCGameInstance>(GetGameInstance())->CreateItem(this, WeaponName));
	Weapon->PickUpItem(this);
	Equip->EquipItem(Weapon);
	//Equip->GetWeapon()->ToggleHands();
	Equip->GetWeapon()->GetEquipment()->Begin_OnHands();
	State->SetStateIdle();
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy_AI::MoveForward(float AxisValue)
{
	CheckFalse(State->IsStateIdle());

	FRotator rotator = FRotator(0, GetActorRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACEnemy_AI::MoveRight(float AxisValue)
{
	CheckFalse(State->IsStateIdle());

	FRotator rotator = FRotator(0, GetActorRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACEnemy_AI::Attack()
{
	if (Equip->GetWeapon() != nullptr)
	{
		Equip->GetWeapon()->Do_Action(this, FKey("LeftMouseButton"));
		CLog::Log("ATTACK");
	}
	bCanAttack = false;
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer
	(
		timerHandle,
		FTimerDelegate::CreateLambda([=]() { bCanAttack = true; }),
		5,
		false,
		5
	);
}
