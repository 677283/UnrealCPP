#include "CSkill_Active_Slash.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/ShapeComponent.h"
#include "Skill/Active/Dual_Slash/CSlashProjectile.h"

void UCSkill_Active_Slash::DoSkill()
{
	CheckFalse(State->IsStateIdle());

	OwnerCharacter->PlayAnimMontage(Montage, PlayRatio);
	State->SetStateSkill();
}

void UCSkill_Active_Slash::BeginDoSkill()
{
	FTransform transform;
	transform.SetLocation(OwnerCharacter->GetActorLocation() + FVector(100, 0, 0));
	transform.SetRotation(FQuat(OwnerCharacter->GetActorRotation()));

	FActorSpawnParameters param;
	param.Owner = OwnerCharacter;
	ACSlashProjectile* projectile = OwnerCharacter->GetWorld()->SpawnActor<ACSlashProjectile>(ProjectileClass, transform, param);
	TArray<UShapeComponent*> components;
	projectile->GetComponents<UShapeComponent>(components);
	
	for (UShapeComponent* component : components)
	{
		component->OnComponentBeginOverlap.AddDynamic(this, &UCSkill_Active_Slash::OnComponentBeginOverlap);
	}
}

void UCSkill_Active_Slash::EndDoSkill()
{
	State->SetStateIdle();
}

void UCSkill_Active_Slash::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO 데미지 주기
}