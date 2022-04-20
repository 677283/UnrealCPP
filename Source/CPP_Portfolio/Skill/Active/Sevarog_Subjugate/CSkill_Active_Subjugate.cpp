#include "CSkill_Active_Subjugate.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Skill/Active/Sevarog_Subjugate/CSubjugate_Actor.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"

void UCSkill_Active_Subjugate::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

}

void UCSkill_Active_Subjugate::DoSkill()
{
	Super::DoSkill();
	CheckFalse(State->IsStateIdle());
	
	OwnerCharacter->PlayAnimMontage(Montage);
	State->SetStateSkill();
	OwnerCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->GetActorLocation()));
}

void UCSkill_Active_Subjugate::BeginDoSkill()
{
	Super::BeginDoSkill();

	switch(UKismetMathLibrary::RandomIntegerInRange(0,1))
	{
		case 0:
			Pattern_0();
			break;
		case 1:
			Pattern_1();
			break;
	}
}

void UCSkill_Active_Subjugate::EndDoSkill()
{
	Super::EndDoSkill();
	Cast<ACEnemy_AI_Boss>(OwnerCharacter)->FinishPattern();
	State->SetStateIdle();
}

void UCSkill_Active_Subjugate::Pattern_0()
{
	float distance = 400;
	FVector center = OwnerCharacter->GetActorForwardVector(), left, right;

	left = FRotator(0, -45, 0).RotateVector(center);
	left.Normalize();
	right = FRotator(0, 45, 0).RotateVector(center);
	right.Normalize();
	
	int32 cnt = 5;
	while (cnt--) 
	{
		FTransform transformC, transformL, transformR;
		transformC.SetLocation(OwnerCharacter->GetActorLocation() + center	* distance * (5 - cnt));
		transformL.SetLocation(OwnerCharacter->GetActorLocation() + left	* distance * (5 - cnt));
		transformR.SetLocation(OwnerCharacter->GetActorLocation() + right	* distance * (5 - cnt));
		
		OwnerCharacter->GetWorld()->SpawnActor<ACSubjugate_Actor>(Subgate_Projectile, transformC)->Cast(0.3f * (5-cnt));
		OwnerCharacter->GetWorld()->SpawnActor<ACSubjugate_Actor>(Subgate_Projectile, transformL)->Cast(0.3f * (5-cnt));
		OwnerCharacter->GetWorld()->SpawnActor<ACSubjugate_Actor>(Subgate_Projectile, transformR)->Cast(0.3f * (5-cnt));
	}
}

void UCSkill_Active_Subjugate::Pattern_1()
{
	float distance = 0;
	FVector center = OwnerCharacter->GetActorLocation();

	for (int i = 0; i < 4; i++)
	{
		int32 cnt = 5;

		while (cnt--)
		{
			FRotator rot = FRotator::ZeroRotator;
			FVector dir = FVector(1, 0, 0);
			rot.Yaw = UKismetMathLibrary::RandomFloatInRange(90 * i, 90 * (i + 1));
			distance = UKismetMathLibrary::RandomFloatInRange(200, 1200);
			dir = rot.RotateVector(dir);

			ACSubjugate_Actor* pj = OwnerCharacter->GetWorld()->SpawnActor<ACSubjugate_Actor>(Subgate_Projectile, center + dir * distance, FRotator::ZeroRotator)/*->Cast(UKismetMathLibrary::RandomFloatInRange(0.1f, 1.0f))*/;
			if (!!pj)pj->Cast(UKismetMathLibrary::RandomFloatInRange(0.1f, 1.0f));
		}
	}
}