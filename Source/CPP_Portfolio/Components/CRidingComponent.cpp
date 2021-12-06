#include "CRidingComponent.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Horse/CHorse.h"

UCRidingComponent::UCRidingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCRidingComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetComponents<UShapeComponent>(Collisions);
	SetComponentTickEnabled(false);
}

void UCRidingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCRidingComponent::OnRide(ACHorse* InHorse)
{
	CheckNull(InHorse);
	RidingHorse = InHorse;

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());

	if (equip->GetWeapon()->IsHandsOn())
	{
		equip->GetWeapon()->OffHands();
	}

	for (UShapeComponent* collision : Collisions)
	{
		CollisionEnableds.Add(collision->GetCollisionEnabled());
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	GetOwner()->AttachToActor(RidingHorse,FAttachmentTransformRules::KeepRelativeTransform);
	GetOwner()->SetActorRelativeTransform(FTransform());
}

void UCRidingComponent::OffRide()
{
	for (int32 i=0; i<Collisions.Num(); i++)
	{
		Collisions[i]->SetCollisionEnabled(CollisionEnableds[i]);
	}
}

bool UCRidingComponent::IsRiding()
{
	return RidingHorse ? true : false;
}