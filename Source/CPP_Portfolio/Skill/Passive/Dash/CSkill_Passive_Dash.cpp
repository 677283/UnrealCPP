#include "CSkill_Passive_Dash.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CStateComponent.h"

#include "Particles/ParticleSystem.h"
#include "NiagaraComponent.h"

void UCSkill_Passive_Dash::BeginPlay(class ACharacter* InOwner)
{
	UCSkill::BeginPlay(InOwner);

	Cast<ACPlayer>(InOwner)->SetDash(this);
	State = CHelpers::GetComponent<UCStateComponent>(InOwner);

	ParticleDash = Cast<UParticleSystem>(DashEffect);

	if (!!ParticleDash)
		OnEffect.AddUObject(this, &UCSkill_Passive_Dash::PlayEffect_Particle);
	else
	{
		NiagaraDash = Cast<UNiagaraSystem>(DashEffect);
		OnEffect.AddUObject(this, &UCSkill_Passive_Dash::PlayEffect_Niagara);
	}
}

void UCSkill_Passive_Dash::DoSkill()
{
	CheckTrue(bDash);
	CheckFalse(State->IsStateIdle());

	OwnerCharacter->PlayAnimMontage(DashMontage);

	FRotator rotation = OwnerCharacter->GetController()->GetControlRotation();
	rotation.Pitch = 0;
	rotation.Roll = 0;

	OwnerCharacter->SetActorRotation(rotation);

	bDash = true;
	State->SetStateSkill();
}

void UCSkill_Passive_Dash::BeginDoSkill()
{
	if (OnEffect.IsBound())
		OnEffect.Broadcast();
}

void UCSkill_Passive_Dash::EndDoSkill()
{
	State->SetStateIdle();
	bDash = false;
}

void UCSkill_Passive_Dash::PlayEffect_Particle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleDash, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
}

void UCSkill_Passive_Dash::PlayEffect_Niagara()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraDash, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
}
