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
	FVector vector = OwnerCharacter->GetActorForwardVector() * 900;
	transform.SetLocation(OwnerCharacter->GetActorLocation() + vector);
	transform.SetLocation(FVector(transform.GetLocation().X, transform.GetLocation().Y, transform.GetLocation().Z + 300));
	transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	ACBow_Ultimate_Dragon* projectile = OwnerCharacter->GetWorld()->SpawnActor<ACBow_Ultimate_Dragon>(ProjectileClass, transform, param);
	projectile->SetActorScale3D(FVector(5, 5, 5));
	//transform.SetRotation(FQuat(transform.GetRotation().X, 90.f, transform.GetRotation().Z, transform.GetRotation().W));
	UParticleSystemComponent* particle = UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), Particle, transform);
	
	FRotator rotate = particle->GetComponentRotation();
	particle->SetRelativeRotation(FRotator(rotate.Pitch, rotate.Yaw, rotate.Roll + 90));
	particle->SetWorldScale3D(FVector(1.5, 1.5, 1.5));
	
	FTimerHandle handle;
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(handle, [=]() {particle->DestroyComponent(); }, 3, false, 3);
}

void UCSkill_Active_Bow_Ultimate::EndDoSkill()
{
	Super::EndDoSkill();

	State->SetStateIdle();

	
}