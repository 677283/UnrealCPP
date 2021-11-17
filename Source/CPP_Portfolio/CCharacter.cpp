#include "CCharacter.h"
#include "Global.h"
#include "Components/CPushingComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

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
	
	Health = MaxHealth;
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

