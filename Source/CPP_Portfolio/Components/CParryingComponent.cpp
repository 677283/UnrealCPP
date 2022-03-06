#include "CParryingComponent.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "GameFramework/Character.h"


UCParryingComponent::UCParryingComponent()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCParryingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SetCollisionProfileName("Parrying");
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnComponentBeginOverlap.AddDynamic(this, &UCParryingComponent::OnBeginOverlap);
}

void UCParryingComponent::DoParry()
{
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	CheckFalse(state->IsStateIdle());

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());
	if (NeedWeapons.Num() > 0)
	{
		int32 typeSum = 0;
		int32 weaponType = (int32)(equip->GetWeapon()->GetWeaponType());


		for (EWeaponType type : NeedWeapons)
		{
			typeSum += pow(2, (int32)type);
		}

		if (!(typeSum | weaponType))
			return;
	}
	
	state->SetStateAction();
	OwnerCharacter->PlayAnimMontage(ParryingMontage);

}

void UCParryingComponent::EndDoParry()
{
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	state->SetStateIdle();
}

void UCParryingComponent::OnCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UCParryingComponent::OffCollision()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UCParryingComponent::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CLog::Log("parryingEnter");
	ACEquipActor* weapon = Cast<ACEquipActor>(OtherActor);
	CheckNull(weapon);
	CheckTrue(OtherActor->GetOwner() == OwnerCharacter);
	

	FVector ownerForwardVector = OwnerCharacter->GetActorForwardVector();
	FVector actorLookVector = OtherActor->GetOwner()->GetActorLocation() - OwnerCharacter->GetActorLocation();
	actorLookVector.Normalize();
	float dot = UKismetMathLibrary::Dot_VectorVector(ownerForwardVector, actorLookVector);

	CLog::Log(dot);

	CheckTrue(dot < 0.3f);

	OtherActor->GetOwner()->TakeDamage(0, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	
}
