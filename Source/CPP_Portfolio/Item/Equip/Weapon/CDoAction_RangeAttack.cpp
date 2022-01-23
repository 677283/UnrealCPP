#include "CDoAction_RangeAttack.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CProjectileActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UCDoAction_RangeAttack::DoAction(FKey InKey)
{
	Super::DoAction(InKey);
	CheckFalse(bCanShot);
	CheckFalse(State->IsStateIdle());
	CheckFalse(*bHands);
	OwnerCharacter->PlayAnimMontage(ShotMontage);
	State->SetStateAction();
	bCanShot = false;
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer
	(
		TimerHandle,
		this,
		&UCDoAction_RangeAttack::CountDelay,
		OwnerCharacter->GetWorld()->GetDeltaSeconds(),
		true
	);
}

void UCDoAction_RangeAttack::BeginDoAction()
{
	Super::BeginDoAction();
	
	AActor* projectile = OwnerCharacter->GetWorld()->SpawnActor(ProjectileClass);
	
	projectile->SetActorLocation(OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 50);
	projectile->SetActorRotation(OwnerCharacter->GetActorRotation());
	
	UProjectileMovementComponent* pj;
	pj = CHelpers::GetComponent<UProjectileMovementComponent>(projectile);
	
	pj->Velocity = projectile->GetActorForwardVector() * 1000;
}

void UCDoAction_RangeAttack::EndDoAction()
{
	Super::EndDoAction();

	State->SetStateIdle();
}

void UCDoAction_RangeAttack::CountDelay()
{
	StackDelay += OwnerCharacter->GetWorld()->GetDeltaSeconds();

	if (StackDelay >= ShotDelay)
	{
		StackDelay = 0;
		bCanShot = true;
		OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}
