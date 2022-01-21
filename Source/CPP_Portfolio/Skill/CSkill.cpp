#include "CSkill.h"
#include "GameFramework/Character.h"

void UCSkill::BeginPlay(ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}

void UCSkill::DoSkill()
{
	CooldownStack = Cooldown;
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(CooldownHandle, this, &UCSkill::CooldownTick, OwnerCharacter->GetWorld()->GetDeltaSeconds(), true);

}

void UCSkill::CooldownTick()
{
	CooldownStack -= GetWorld()->GetDeltaSeconds();

	if (CooldownStack < 0.0f)
		OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(CooldownHandle);
	
	OnCooldown.ExecuteIfBound();
}