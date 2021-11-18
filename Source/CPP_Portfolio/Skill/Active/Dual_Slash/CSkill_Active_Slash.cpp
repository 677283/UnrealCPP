#include "CSkill_Active_Slash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/ShapeComponent.h"
#include "Animation/AnimMontage.h"
#include "Skill/Active/Dual_Slash/CSlashProjectile.h"

UCSkill_Active_Slash::UCSkill_Active_Slash()
{
	CHelpers::GetAsset<UAnimMontage>(&Montage, "AnimMontage'/Game/__ProjectFile/Montages/Dual/Frank_RPG_Dual_Skill04_InfinitySlash_Montage.Frank_RPG_Dual_Skill04_InfinitySlash_Montage'");
}

void UCSkill_Active_Slash::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

}

void UCSkill_Active_Slash::DoSkill()
{
	Super::DoSkill();

	CheckFalse(State->IsStateIdle());
	CheckFalse(WeaponCheck());

	OwnerCharacter->PlayAnimMontage(Montage, PlayRatio);
	State->SetStateSkill();
}

void UCSkill_Active_Slash::BeginDoSkill()
{
	Super::BeginDoSkill();

	FTransform transform;
	FVector vector = OwnerCharacter->GetActorForwardVector() * 100;
	transform.SetLocation(OwnerCharacter->GetActorLocation() + vector);
	transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;

	ACSlashProjectile* projectile = OwnerCharacter->GetWorld()->SpawnActor<ACSlashProjectile>(ProjectileClass, transform, param);
}

void UCSkill_Active_Slash::EndDoSkill()
{
	Super::EndDoSkill();

	State->SetStateIdle();
}