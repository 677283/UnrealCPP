#include "CBoomerang_Throw.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CStateComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "Skill/CSkill.h"

ACBoomerang_Throw::ACBoomerang_Throw()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* scene;

	CHelpers::CreateComponent <USceneComponent> (this, &scene, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", scene);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");
	
	Mesh->SetCollisionProfileName("NoCollision");

	Projectile->ProjectileGravityScale = 0;
	Projectile->MaxSpeed = 3000;
}

void ACBoomerang_Throw::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator::ZeroRotator);

	Mesh->SetRelativeRotation(FRotator(0, 0, 90));
	Mesh->AddLocalRotation(-1 * Comps[0]->GetRelativeRotation());

	SetActorRotation(GetOwner()->GetActorRotation());
	AddActorWorldRotation(FRotator(0, Direction * 20, 0));

	AddActorWorldOffset(GetOwner()->GetActorForwardVector() * 400);

	Projectile->SetVelocityInLocalSpace(FVector(100, 0, 0));

	for (UShapeComponent* comp : Comps)
	{
		comp->SetCollisionProfileName("Boomerang");
	}
}

void ACBoomerang_Throw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InterpSpeed += DeltaTime * InterpUpdateSpeed;
	UKismetMathLibrary::FClamp(InterpSpeed, 0, InterpSpeedMax);
	Mesh->AddWorldRotation(FRotator(0, Direction * RotateSpeed * DeltaTime, 0));

	FRotator rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetOwner()->GetActorLocation());

	rotator = UKismetMathLibrary::RInterpTo(GetActorRotation(), rotator, DeltaTime, InterpSpeed);

	SetActorRotation(rotator);

	Projectile->SetVelocityInLocalSpace(FVector(ProjectileVelocity, 0, 0));
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
	Skill = InSkill;
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