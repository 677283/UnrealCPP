#include "CBoomerang_Throw.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "Skill/CSkill.h"

ACBoomerang_Throw::ACBoomerang_Throw()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	Mesh->SetCollisionProfileName("NoCollision");
}

void ACBoomerang_Throw::BeginPlay()
{
	Super::BeginPlay();

	//SetActorRotation(FRotator::ZeroRotator);
	SetActorRotation(FRotator(0, 0, 90));
	CLog::Log(Comps[0]->GetRelativeRotation());
	AddActorLocalRotation(-1 * Comps[0]->GetRelativeRotation());
	AddActorWorldOffset(GetOwner()->GetActorForwardVector() * 400);
	/*sphere = NewObject<USphereComponent>(this);

	sphere->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	sphere->RegisterComponent();

	sphere->OnComponentBeginOverlap.AddDynamic(this, &ACBoomerang_Throw::OnComponentBeginOverlap);

	sphere->SetHiddenInGame(false);

	sphere->SetCollisionProfileName("Test");*/
}

void ACBoomerang_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0, Direction * 1680 * DeltaTime, 0));
}

void ACBoomerang_Throw::SetBoomerang(class UCSkill* InSkill, class AActor* InWeapon, int32 InDirection)
{
	CheckNull(InWeapon);
	USkeletalMeshComponent* skeletal = CHelpers::GetComponent<USkeletalMeshComponent>(InWeapon);

	Mesh->SetSkeletalMesh(skeletal->SkeletalMesh);

	TArray<UShapeComponent*> collisions;
	InWeapon->GetComponents<UShapeComponent>(collisions);

	for (UShapeComponent* collision : collisions)
	{
		UShapeComponent* comp = NULL;
		switch (collision->GetCollisionShape().ShapeType)
		{
		case ECollisionShape::Type::Box:
			comp = NewObject<UBoxComponent>(this);
			break;

		case ECollisionShape::Type::Capsule:
			comp = NewObject<UCapsuleComponent>(this);
			break;

		case ECollisionShape::Type::Sphere:
			comp = NewObject<USphereComponent>(this);
			break;
		}

		comp->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

		comp->RegisterComponent();

		comp->OnComponentBeginOverlap.AddDynamic(this, &ACBoomerang_Throw::OnComponentBeginOverlap);
		comp->SetRelativeTransform(collision->GetRelativeTransform());
		Comps.Add(comp);
	}

	Weapon = InWeapon;

	Direction = InDirection;
}

void ACBoomerang_Throw::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == GetOwner())
	{
		Skill->EndDoSkill();
		return;
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(OtherActor);
}