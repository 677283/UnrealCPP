#include "CParryingComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponItem.h"

UCParryingComponent::UCParryingComponent()
{

}

void UCParryingComponent::BeginPlay()
{
	
}

void UCParryingComponent::DoParry()
{
	TArray<AActor*> actors;
	
	GetOverlappingActors(actors, UCWeaponItem::StaticClass());

	if (actors.Num() < 1) return;

	for (AActor* actor : actors)
		actor->TakeDamage(0, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
}
