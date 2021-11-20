#include "CSkill_Active_Throw.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/Dual/CEquipActor_Dual.h"
#include "Skill/ACtive/Dual_Throw/CBoomerang_Throw.h"

UCSkill_Active_Throw::UCSkill_Active_Throw()
{

}

void UCSkill_Active_Throw::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);
	
}

void UCSkill_Active_Throw::DoSkill()
{
	Super::DoSkill();

	CheckFalse(State->IsStateIdle());

	OwnerCharacter->PlayAnimMontage(Montage);
	State->SetStateSkill();
}

void UCSkill_Active_Throw::BeginDoSkill()
{
	Super::BeginDoSkill();

	Weapon = Cast<ACEquipActor_Dual>(CHelpers::GetComponent<UCEquipComponent>(OwnerCharacter)->GetWeapon()->GetEquipActor());

	FTransform transform;

	ACBoomerang_Throw* boomerang = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACBoomerang_Throw>(ACBoomerang_Throw::StaticClass(), transform, OwnerCharacter, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	boomerang->SetBoomerang(this, Weapon, 1);
	Boomerangs.Add(boomerang);
	transform = Weapon->GetActorTransform();
	UGameplayStatics::FinishSpawningActor(boomerang, transform);
	
	boomerang = OwnerCharacter->GetWorld()->SpawnActorDeferred<ACBoomerang_Throw>(ACBoomerang_Throw::StaticClass(), transform, OwnerCharacter, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	boomerang->SetBoomerang(this, Weapon->GetSubWeapon(), -1);
	Boomerangs.Add(boomerang);
	transform = Weapon->GetSubWeapon()->GetActorTransform();
	UGameplayStatics::FinishSpawningActor(boomerang, transform);

	Weapon->SetVisibility(false);
	Weapon->GetSubWeapon()->SetVisibility(false);
}

void UCSkill_Active_Throw::EndDoSkill()
{
	Super::EndDoSkill();

	for (AActor* boomerang : Boomerangs)
	{
		boomerang->Destroy();
	}

	Boomerangs.Empty();

	Weapon->SetVisibility(true);
	Weapon->GetSubWeapon()->SetVisibility(true);
}

void UCSkill_Active_Throw::OnBoomerangBeginOverlap(class AActor* OtherActor)
{

}