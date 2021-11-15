#include "CEquipActor.h"
#include "Global.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"

ACEquipActor::ACEquipActor()
{
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "SkeletalMesh");
}

void ACEquipActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UShapeComponent>(Collisions);

	for (UShapeComponent* collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACEquipActor::OnComponentBeginOverlap);
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ACEquipActor::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACEquipActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnEquipActorBeginOverlap.IsBound())
		OnEquipActorBeginOverlap.Broadcast();
}

void ACEquipActor::OnEquipmentToggleHands(FName InSocketName)
{
	AttachTo(InSocketName);
}

void ACEquipActor::OnCollision()
{
	for (UShapeComponent* collision : Collisions)
	{
		collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	if (OnEquipActorCollision.IsBound())
		OnEquipActorCollision.Broadcast();
}

void ACEquipActor::OffCollision()
{
	for (UShapeComponent* collision : Collisions)
	{
		collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (OffEquipActorCollision.IsBound())
		OffEquipActorCollision.Broadcast();
}