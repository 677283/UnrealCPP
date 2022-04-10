#include "CSkill_Active_Subjugate.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "Skill/Active/Sevarog_Subjugate/CSubjugate_Actor.h"

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
	OwnerCharacter->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->GetActorLocation()));
}

void UCSkill_Active_Subjugate::BeginDoSkill()
{
	Super::BeginDoSkill();
	Pattern_0();
	//FTransform transform;
	//transform.SetLocation(UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->GetActorLocation());
	//
	//FActorSpawnParameters param;
	//param.Owner = OwnerCharacter;
	//
	//OwnerCharacter->GetWorld()->SpawnActor<AActor>(Subgate_Projectile, transform, param);
	//UGameplayStatics::SpawnEmitterAtLocation(OwnerCharacter->GetWorld(), Particle, );
}

void UCSkill_Active_Subjugate::EndDoSkill()
{
	Super::EndDoSkill();
	State->SetStateIdle();
}

void UCSkill_Active_Subjugate::Pattern_0()
{
	float distance = 200;
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

}