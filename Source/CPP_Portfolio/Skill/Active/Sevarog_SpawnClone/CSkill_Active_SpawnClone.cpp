#include "CSkill_Active_SpawnClone.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Enemy/AI/CEnemy_AI.h"

void UCSkill_Active_SpawnClone::BeginPlay(ACharacter * InOwner)
{
	Super::BeginPlay(InOwner);

}

void UCSkill_Active_SpawnClone::DoSkill()
{
	Super::DoSkill();

	OwnerCharacter->PlayAnimMontage(Montage);
	State->SetStateSkill();
}

void UCSkill_Active_SpawnClone::BeginDoSkill()
{
	Super::BeginDoSkill();

	SpawnCountCheck = SpawnCount;

	OwnerCharacter->GetOwner()->GetWorldTimerManager().SetTimer(SpawnCloneTimerHandle, this, &UCSkill_Active_SpawnClone::SpawnCloneTimer, 1, true, 2);
}

void UCSkill_Active_SpawnClone::EndDoSkill()
{
	Super::EndDoSkill();

	State->SetStateIdle();
}

void UCSkill_Active_SpawnClone::SpawnCloneTimer()
{
	SpawnCountCheck--;
	FVector targetPos = UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->GetActorLocation();

	FVector spawnPos = targetPos;
	FVector dir(1, 0, 0);
	dir = dir.RotateAngleAxis(UKismetMathLibrary::RandomFloatInRange(0, 360), FVector(0, 0, 1));
	spawnPos += dir * SpawnRange;
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(spawnPos, targetPos);
	spawnPos.Z = OwnerCharacter->GetActorLocation().Z;
	OwnerCharacter->GetWorld()->SpawnActor<AActor>(CloneClass, spawnPos, rot);

	if (SpawnCountCheck == 0)
	{
		OwnerCharacter->GetWorld()->GetTimerManager().ClearTimer(SpawnCloneTimerHandle);
	}
}