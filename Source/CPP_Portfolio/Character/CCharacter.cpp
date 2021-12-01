#include "CCharacter.h"
#include "Global.h"
#include "Components/CPushingComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Item/Equip/Weapon/CDoAction.h"

#define ACCharacter_DEBUG

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UCPushingComponent>(this, &Pushing, "Pushing", GetRootComponent());
	CHelpers::CreateActorComponent<UCEquipComponent>(this, &Equip, "Equip");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ACCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	const FCustomDamageEvent* damageEvent = (FCustomDamageEvent *)&DamageEvent;
	
	float life = Status->SetLife(-Damage);
	if (life > 0)
	{
		if (!!damageEvent->HitMontage)
			PlayAnimMontage(damageEvent->HitMontage, damageEvent->PlayRatio);
		else
			PlayAnimMontage(DefaultHitMontage, DefaultHitMontagePlayRitio);
	}
	else 
	{
		//TODO Death
	}

	return Damage;
}