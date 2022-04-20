#include "CEnemy_AI_Boss.h"
#include "Global.h"
#include "Components/CSkillComponent.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Skill/Active/Sevarog_Subjugate/CSkill_Active_Subjugate.h"
#include "Skill/Active/Sevarog_SpawnClone/CSkill_Active_SpawnClone.h"
#include "Skill/Active/Sevarog_Fence/CSkill_Active_Fence.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

void ACEnemy_AI_Boss::BeginPlay()
{
	Super::BeginPlay();

	Weapon->OnHands();
	OriMaterials = GetMesh()->GetMaterials();
	
	Subjugate = NewObject<UCSkill_Active_Subjugate>(this,SubjugateClass);
	Subjugate->BeginPlay(this);
	Skill->AddSkill(Subjugate);
	
	SpawnClone = NewObject<UCSkill_Active_SpawnClone>(this, SpawnCloneClass);
	SpawnClone->BeginPlay(this);
	Skill->AddSkill(SpawnClone);

	Fence = NewObject<UCSkill_Active_Fence>(this, FenceClass);
	Fence->BeginPlay(this);
	Skill->AddSkill(Fence);

	DisMatDynamic = UMaterialInstanceDynamic::Create(DisMatConst, DisMatDynamic);
}

void ACEnemy_AI_Boss::Hidding()
{
}

void ACEnemy_AI_Boss::CastSubjugate()
{
	Subjugate->DoSkill();
}

void ACEnemy_AI_Boss::Dash()
{
	SpawnClone->DoSkill();
	ChangeMat(false);
}

void ACEnemy_AI_Boss::EndDash()
{
	ChangeMat(true);
}

void ACEnemy_AI_Boss::CastFence()
{
	Fence->DoSkill();
}

void ACEnemy_AI_Boss::ChangeMat(bool flag)
{
	if (flag)
	{
		for (int i=0;i<OriMaterials.Num();i++)
			GetMesh()->SetMaterial(i, OriMaterials[i]);
	}
	else
	{
		for (int i = 0; i < OriMaterials.Num(); i++)
			GetMesh()->SetMaterial(i, DisMatDynamic);
		GetWorldTimerManager().SetTimer<ACEnemy_AI_Boss>(DisHandle, this, &ACEnemy_AI_Boss::DisTimer, GetWorld()->GetDeltaSeconds(), true);
		UNiagaraFunctionLibrary::SpawnSystemAttached(DashEffect, GetMesh(), "", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::KeepRelativeOffset, true);
	}
}

void ACEnemy_AI_Boss::DisTimer()
{
	DisMatDynamic->SetScalarParameterValue("Dissolve", DissolvePower);
	DissolvePower += 1 * GetWorldTimerManager().GetTimerRate(DisHandle);
	
	if (DissolvePower >= 1.0f)
	{
		DisMatDynamic->SetScalarParameterValue("Dissolve", 1);
		DissolvePower = 0.0f;
		GetWorldTimerManager().ClearTimer(DisHandle);
	}
}