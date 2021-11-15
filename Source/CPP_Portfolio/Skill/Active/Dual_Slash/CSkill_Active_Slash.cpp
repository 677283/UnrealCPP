#include "CSkill_Active_Slash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"

void UCSkill_Active_Slash::DoSkill()
{
	CheckFalse(State->IsStateIdle());

	OwnerCharacter->PlayAnimMontage(Montage, PlayRatio);
}

void UCSkill_Active_Slash::BeginDoSkill()
{
	FTransform transform;
	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;
	ACSlashProjectile* projectile = OwnerCharacter->GetWorld()->SpawnActor<ACSlashProjectile>(ProjectileClass, transform, param);

}

void UCSkill_Active_Slash::EndDoSkill()
{

}