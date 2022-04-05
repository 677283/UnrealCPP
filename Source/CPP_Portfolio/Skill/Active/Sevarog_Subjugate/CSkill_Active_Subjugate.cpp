#include "CSkill_Active_Subjugate.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "particles/ParticleSystemComponent.h"

void UCSkill_Active_Subjugate::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	//UParticleSystemComponent* particle;

}

void UCSkill_Active_Subjugate::DoSkill()
{
	Super::DoSkill();
	CheckFalse(State->IsStateIdle());
	
	OwnerCharacter->PlayAnimMontage(Montage);
	State->SetStateSkill();
}

void UCSkill_Active_Subjugate::BeginDoSkill()
{
	Super::BeginDoSkill();

	FTransform transform;
	transform.SetLocation(UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->GetActorLocation());

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	OwnerCharacter->GetWorld()->SpawnActor<AActor>(Subgate_Projectile, transform, param);
	//UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), Particle, );
}

void UCSkill_Active_Subjugate::EndDoSkill()
{
	Super::EndDoSkill();
	State->SetStateIdle();
}