#include "CSkill_Active_Bow_Ultimate.h"
#include "Global.h"
#include "CBow_Ultimate_Dragon.h"
#include "Components/CStateComponent.h"
#include "Particles/ParticleSystemComponent.h"

UCSkill_Active_Bow_Ultimate::UCSkill_Active_Bow_Ultimate()
{
	CHelpers::GetAsset<UAnimMontage>(&Montage, "AnimMontage'/Game/__ProjectFile/Montages/Bow/Frank_RPG_Archer_Combo04_03_Montage.Frank_RPG_Archer_Combo04_03_Montage'");
	//CHelpers::
}

void UCSkill_Active_Bow_Ultimate::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

}

void UCSkill_Active_Bow_Ultimate::DoSkill()
{
	Super::DoSkill();

	CheckFalse(State->IsStateIdle());
	CheckFalse(WeaponCheck());

	OwnerCharacter->PlayAnimMontage(Montage, PlayRatio);
	State->SetStateSkill();
}

void UCSkill_Active_Bow_Ultimate::BeginDoSkill()
{
	Super::BeginDoSkill();

	FTransform transform;
	FVector vector = OwnerCharacter->GetActorForwardVector() * 100;
	transform.SetLocation(OwnerCharacter->GetActorLocation() + vector);
	transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	ACBow_Ultimate_Dragon* projectile = OwnerCharacter->GetWorld()->SpawnActor<ACBow_Ultimate_Dragon>(ProjectileClass, transform, param);
	ParticleComponent = UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), Particle, transform);

	FTimerHandle handle;
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(handle, [=]() {ParticleComponent->DestroyComponent(); }, 3, false, 3);
}

void UCSkill_Active_Bow_Ultimate::EndDoSkill()
{
	Super::EndDoSkill();

	State->SetStateIdle();

	
}