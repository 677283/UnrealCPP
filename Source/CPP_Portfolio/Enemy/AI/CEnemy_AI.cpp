#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Components/CStateComponent.h"

#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "CGameInstance.h"

#include "Item/Equip/Weapon/CDoAction.h"

#include "Components/TextRenderComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", GetRootComponent());
	Text->Text = FText::FromString(FString::SanitizeFloat(RemineTime));
}

void ACEnemy_AI::BeginPlay()
{
	Super::BeginPlay();

	Weapon = Cast<UCWeaponItem>(Cast<UCGameInstance>(GetGameInstance())->CreateItem(this, WeaponName));
	Weapon->PickUpItem(this);
	Equip->EquipItem(Weapon);
	State->SetStateIdle();
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RemineTime > 0)
	{
		RemineTime -= DeltaTime;
	}
	else
	{
		RemineTime = 0;
		SetActorTickEnabled(false);
	}
	Text->SetText(FText::FromString(FString::Printf(TEXT("%.2f"),RemineTime)));
	
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

void ACEnemy_AI::EquipWeapon()
{
	Equip->GetWeapon()->OnHands();
}

void ACEnemy_AI::UnequipWeapon()
{
	Equip->GetWeapon()->OffHands();
}

void ACEnemy_AI::Attack()
{
	if (Equip->GetWeapon() != nullptr)
	{
		Equip->GetWeapon()->Do_Action(this, FKey("LeftMouseButton"));
	}
	
	if (Equip->GetWeapon()->GetDoAction()->GetAttackCnt() < MaxAttackCnt)
		return;

	Equip->GetWeapon()->GetDoAction()->InitializeCount();
	
	MaxAttackCnt = UKismetMathLibrary::RandomIntegerInRange(1, 4);
	CLog::Log(MaxAttackCnt);
	bCanAttack = false;

	RemineTime = AttackDelay;
	SetActorTickEnabled(true);

	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer
	(
		timerHandle,
		FTimerDelegate::CreateLambda([=]() { bCanAttack = true; }),
		AttackDelay,
		false
	);


}
