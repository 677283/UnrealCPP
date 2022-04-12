#include "CSkill_Passive_Dash.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CStateComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
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

	SubCam = OwnerCharacter->GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	SubCam->GetCameraComponent()->SetConstraintAspectRatio(false);
}

void UCSkill_Passive_Dash::DoSkill()
{
	CheckTrue(bDash);
	CheckFalse(State->IsStateIdle());

	UCameraComponent* cam = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	SubCam->SetActorTransform(cam->GetComponentTransform());
	APlayerController* pc = Cast<APlayerController>(OwnerCharacter->GetController());
	pc->SetViewTarget(SubCam);

	FRotator rot = OwnerCharacter->GetController()->GetControlRotation();
	rot.Roll = 0;
	rot.Pitch = 0;
	OwnerCharacter->SetActorRotation(rot);
	FVector dir = OwnerCharacter->GetActorForwardVector();
	OwnerCharacter->SetActorLocation(OwnerCharacter->GetActorLocation() + dir * DashDisatnce);

	/*

	FRotator rotation = OwnerCharacter->GetController()->GetControlRotation();
	rotation.Pitch = 0;
	rotation.Roll = 0;
	FVector dir = OwnerCharacter->GetActorForwardVector();
	FRotator rot = UKismetMathLibrary::NormalizedDeltaRotator(OwnerCharacter->GetController()->GetControlRotation(), OwnerCharacter->GetActorRotation());
	rot.Pitch = 0;
	rot.Roll = 0;
	CLog::Log(rot);
	dir = rot.RotateVector(dir);
	CLog::Log(dir);
	FVector pos = OwnerCharacter->GetActorLocation();
	pos += dir * DashDisatnce;
	OwnerCharacter->SetActorLocation(pos);

	OwnerCharacter->SetActorRotation(rotation);
	*/

	OwnerCharacter->PlayAnimMontage(DashMontage);
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

	UCameraComponent* cam = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	APlayerController* pc = Cast<APlayerController>(OwnerCharacter->GetController());
	pc->SetViewTargetWithBlend(OwnerCharacter, 0.5f);
}

void UCSkill_Passive_Dash::PlayEffect_Particle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleDash, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
}

void UCSkill_Passive_Dash::PlayEffect_Niagara()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraDash, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
}
