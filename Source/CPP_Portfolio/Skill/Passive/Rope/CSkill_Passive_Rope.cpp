#include "CSkill_Passive_Rope.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Skill/Passive/Rope/CRope.h"
#include "GameFramework/CharacterMovementComponent.h"

UCSkill_Passive_Rope::UCSkill_Passive_Rope()
{
	 
}

void UCSkill_Passive_Rope::BeginPlay(ACharacter * InOwner)
{
	Super::BeginPlay(InOwner);
	Rope = Cast<ACRope>(OwnerCharacter->GetWorld()->SpawnActor(RopeClass));
	Rope->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "Hand_L");
}

void UCSkill_Passive_Rope::DoSkill()
{
	Super::DoSkill();

	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	CheckNull(state);

	CheckFalse(state->IsStateIdle());

	OwnerCharacter->PlayAnimMontage(Montage);

	state->SetStateSkill();
	
	CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter)->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCSkill_Passive_Rope::BeginDoSkill()
{
	Super::BeginDoSkill();
	
	FVector dir = OwnerCharacter->GetActorForwardVector();
	dir = dir.RotateAngleAxis(-25, OwnerCharacter->GetActorRightVector());
	Rope->SetTargetPosition(dir);
}

void UCSkill_Passive_Rope::EndDoSkill()
{
	Super::EndDoSkill();
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	state->SetStateIdle();
	Rope->OffParticle();
	CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter)->SetMovementMode(EMovementMode::MOVE_Walking);
}
