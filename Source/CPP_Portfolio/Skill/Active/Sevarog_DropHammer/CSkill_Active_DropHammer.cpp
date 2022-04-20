#include "CSkill_Active_DropHammer.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Components/CStateComponent.h"
#include "Item/CItemStructures.h"

UCSkill_Active_DropHammer::UCSkill_Active_DropHammer()
{

}

void UCSkill_Active_DropHammer::BeginPlay(class ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	AActor* collisionObj = OwnerCharacter->GetWorld()->SpawnActor(HammerCollisionCheck);
	collisionObj->AttachToActor(OwnerCharacter,FAttachmentTransformRules::KeepRelativeTransform);
	Collision = CHelpers::GetComponent<USphereComponent>(collisionObj);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &UCSkill_Active_DropHammer::OnComponentBeginOverlap);
}

void UCSkill_Active_DropHammer::DoSkill()
{
	Super::DoSkill();

	OwnerCharacter->PlayAnimMontage(Montage);
	State->SetStateSkill();
}

void UCSkill_Active_DropHammer::BeginDoSkill()
{
	Super::BeginDoSkill();
	OnCollision();
	FTimerHandle handle;
	OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(handle, this, &UCSkill_Active_DropHammer::OffCollisionTimer, 1.0f, false);
}

void UCSkill_Active_DropHammer::EndDoSkill()
{
	Super::EndDoSkill();
	State->SetStateIdle();
}

void UCSkill_Active_DropHammer::OnCollision()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UCSkill_Active_DropHammer::OffCollision()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCSkill_Active_DropHammer::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	FCustomDamageEvent damageEvent;
	//damageEvent.AttackLevel = 2;
	//damageEvent.LaunchDirectAngle = FQuat(0, 180, 0, 0);
	//damageEvent.LaunchPower = 100.0f;
	OtherActor->TakeDamage(Damage, damageEvent, OwnerCharacter->GetController(), OwnerCharacter);
}

void UCSkill_Active_DropHammer::OffCollisionTimer()
{
	OffCollision();
}