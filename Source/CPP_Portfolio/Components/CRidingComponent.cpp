#include "CRidingComponent.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Components/CEquipComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Horse/CHorse.h"

#define LEFT 0
#define RIGHT 1

#define BACK 0
#define MID 1
#define FRONT 3

UCRidingComponent::UCRidingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	OwnerCharacter = Cast<ACharacter>(GetOwner());
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
	RidingHorse->SetRider(Cast<ACCharacter>(OwnerCharacter));
	
	FVector find = OwnerCharacter->GetActorLocation() - RidingHorse->GetActorLocation();
	find.Normalize();
	
	float dot = UKismetMathLibrary::Dot_VectorVector(RidingHorse->GetActorForwardVector(), find);	
	FVector cross = UKismetMathLibrary::Cross_VectorVector(RidingHorse->GetActorForwardVector(), find);
	float crossDot = UKismetMathLibrary::Dot_VectorVector(cross, FVector::UpVector);
	int fIdx;
	crossDot > 0 ? fIdx = LEFT : fIdx = RIGHT;

	if (dot > 0.5f)
	{
		OwnerCharacter->PlayAnimMontage(MountMontage[fIdx + FRONT]);
	}
	else if (dot > -0.5f)
	{
		OwnerCharacter->PlayAnimMontage(MountMontage[fIdx + MID]);
	}
	else
	{
		OwnerCharacter->PlayAnimMontage(MountMontage[BACK]);
	}	

	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());

	if (!!equip->GetWeapon())
	{
		if (equip->GetWeapon()->IsHandsOn())
		{
			equip->GetWeapon()->OffHands();
		}
	}

	for (UShapeComponent* collision : Collisions)
	{
		CollisionEnableds.Add(collision->GetCollisionEnabled());
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	GetOwner()->AttachToActor(RidingHorse,FAttachmentTransformRules::KeepRelativeTransform);
	GetOwner()->SetActorRelativeTransform(FTransform());
	bRiding = true;
}

void UCRidingComponent::BeginOnRide()
{
	OwnerCharacter->GetController()->Possess(RidingHorse);
}

void UCRidingComponent::OffRide()
{
	GetOwner()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UMovementComponent* movement = CHelpers::GetComponent<UMovementComponent>(RidingHorse);
	movement->Velocity = FVector::ZeroVector;


	for (int32 i=0; i<Collisions.Num(); i++)
	{
		Collisions[i]->SetCollisionEnabled(CollisionEnableds[i]);
	}

	RidingHorse = nullptr;
	bRiding = false;
}

void UCRidingComponent::BeginOffRide()
{
	RidingHorse->GetController()->Possess(OwnerCharacter);
}
