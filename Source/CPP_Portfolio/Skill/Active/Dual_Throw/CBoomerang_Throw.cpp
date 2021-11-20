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
}

void ACBoomerang_Throw::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(Weapon->GetActorLocation() + Weapon->GetActorForwardVector() * 100);

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

}

void ACBoomerang_Throw::SetBoomerang(class UCSkill* InSkill, class AActor* InWeapon)
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
	}

	if (collisions[0]->GetUpVector() == FVector::UpVector || collisions[0]->GetUpVector() == (-1 * FVector::UpVector) ||
		collisions[0]->GetForwardVector() == FVector::UpVector || collisions[0]->GetForwardVector() == (-1 * FVector::UpVector))
	{
		collisions[0]->SetRelativeRotation(FQuat(FRotator(0, 0, 90)));
	}

	Weapon = InWeapon;
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