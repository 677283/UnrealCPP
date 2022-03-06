#include "CSkill_Active_JumpSmash.h"

void UCSkill_Active_JumpSmash::BeginPlay(ACharacter * InOwner)
{
	Super::BeginPlay(InOwner);
}

void UCSkill_Active_JumpSmash::DoSkill()
{
	Super::DoSkill();

	OwnerCharacter->PlayAnimMontage(Montage);
}

void UCSkill_Active_JumpSmash::BeginDoSkill()
{
	Super::BeginDoSkill();
}

void UCSkill_Active_JumpSmash::EndDoSkill()
{
	Super::EndDoSkill();

}
