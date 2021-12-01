#include "CEquipActor.h"
#include "Global.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/Character.h"

ACEquipActor::ACEquipActor()
{
	USceneComponent* scene;
	CHelpers::CreateComponent<USceneComponent>(this, &scene, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "SkeletalMesh", scene);
	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetVisibility(false);
}

void ACEquipActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UShapeComponent>(Collisions);

	for (UShapeComponent* collision : Collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACEquipActor::OnComponentBeginOverlap);
		collision->SetCollisionProfileName("Weapon");
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OffCollision();
}

void ACEquipActor::AttachTo(FName InSocketName)
{
	CheckNull(OwnerCharacter);
	
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACEquipActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter

	CheckTrue(OtherActor == OwnerCharacter);

	ACharacter* otherCharacter = Cast<ACharacter>(OtherActor);
	if (OnEquipActorBeginOverlap.IsBound())
		OnEquipActorBeginOverlap.Broadcast(OwnerCharacter, this, otherCharacter);
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

void ACEquipActor::SetVisibility(bool InBool)
{
	Mesh->SetVisibility(InBool);
}

void ACEquipActor::SetOwnerCharacter(class ACharacter* InOwner)
{
	SetOwner(InOwner);
	OwnerCharacter = InOwner;
}

void ACEquipActor::Equip()
{
	Mesh->SetVisibility(true);
}

void ACEquipActor::Unequip()
{
	Mesh->SetVisibility(false);
}