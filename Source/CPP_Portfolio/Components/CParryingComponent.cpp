#include "CParryingComponent.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "GameFramework/Character.h"


UCParryingComponent::UCParryingComponent()
{

}

void UCParryingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SetCollisionProfileName("Parrying");
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

	TArray<AActor*> actors;
	
	GetOverlappingActors(actors, ACEquipActor::StaticClass());

	if (actors.Num() < 1) return;

	for (AActor* actor : actors)
	{
		ACEquipActor* weapon = Cast<ACEquipActor>(actor);
		if (weapon == nullptr)
		{
			actors.Remove(actor);
			continue;
		}

		if (actor->GetOwner() == OwnerCharacter)
			actors.Remove(actor);
	}
	
	for (AActor* actor : actors)
		actor->GetOwner()->TakeDamage(0, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
}

void UCParryingComponent::EndDoParry()
{
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	state->SetStateIdle();
}
