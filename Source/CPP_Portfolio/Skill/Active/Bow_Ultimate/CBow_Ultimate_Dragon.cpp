#include "CBow_Ultimate_Dragon.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"

ACBow_Ultimate_Dragon::ACBow_Ultimate_Dragon()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root;
	CHelpers::CreateComponent<USceneComponent>(this, &root, "Root");
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Mesh_1, "Mesh_1", root);
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Mesh_2, "Mesh_2", root);
	CHelpers::CreateComponent<UCapsuleComponent>(this, &Collision, "Capsule", root);
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	USkeletalMesh* mesh;
	CHelpers::GetAsset(&mesh, "SkeletalMesh'/Game/KiAuras/Characters/RotatingDragon/DragonRotation.DragonRotation'");
	Mesh_1->SetSkeletalMesh(mesh);
	Mesh_2->SetSkeletalMesh(mesh);

}

void ACBow_Ultimate_Dragon::BeginPlay()
{
	Super::BeginPlay();
	
	BoneAllName = Mesh_1->GetAllSocketNames();
	BoneAllName.Remove("Armature");
	BoneAllName.Remove("Bone");
	//BoneAllName.Remove("Bone_029_end");
	//BoneAllName.Remove("Bone_029_end_end");
	//BoneAllName.Remove("ncl1_1");

	BodyScale = Mesh_1->GetBoneScaleByName("Bone_001", EBoneSpaces::ComponentSpace);
}

void ACBow_Ultimate_Dragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Scale = FMath::Clamp(Scale, 0.0f, 1.0f);

	FVector subDir;
	FVector subDir2;

	Direction = HeadRotate.RotateVector(Direction);

	subDir = Direction;
	subDir2 = -Direction;

	Mesh_1->SetBoneLocationByName("Bone", Direction * Radius, EBoneSpaces::ComponentSpace);
	Mesh_2->SetBoneLocationByName("Bone", -Direction * Radius, EBoneSpaces::ComponentSpace);

	float subGap = 0;
	StretchGap += Stretch * DeltaTime;
	StretchGap = FMath::Clamp(StretchGap, 0.0f, BodyGap);

	for (FName name : BoneAllName)
	{
		subDir = BodyRotate.RotateVector(subDir);
		subDir2 = BodyRotate.RotateVector(subDir2);

		FVector pos = subDir * Radius;
		FVector pos2 = subDir2 * Radius;

		pos.Y -= subGap;
		pos2.Y -= subGap;

		subGap += StretchGap;

		Mesh_1->SetBoneLocationByName(name, pos, EBoneSpaces::ComponentSpace);
		Mesh_2->SetBoneLocationByName(name, pos2, EBoneSpaces::ComponentSpace);

	}
}