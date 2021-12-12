#include "CTestActor.h"
#include "Global.h"
#include "Components/PoseableMeshComponent.h"

ACTestActor::ACTestActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* root;
	CHelpers::CreateComponent<USceneComponent>(this, &root, "Root");
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Poseable, "Poseable", root);

	USkeletalMesh* mesh;
	CHelpers::GetAsset(&mesh, "SkeletalMesh'/Game/KiAuras/Characters/RotatingDragon/DragonRotation.DragonRotation'");
	Poseable->SetSkeletalMesh(mesh);

	Direction = FVector::UpVector;
}

void ACTestActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<FName> allName = Poseable->GetAllSocketNames();

	for (FName name : allName)
	{
		//Original.Add(Poseable->GetBoneLocation(name, EBoneSpaces)
	}

	if (FMath::IsNearlyZero(Gap))
		Gap = Poseable->GetBoneLocation("Bone", EBoneSpaces::ComponentSpace).Y;
}

void ACTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector subDir;

	Direction = Rotate.RotateVector(Direction);

	subDir = Direction;

	TArray<FName> allName = Poseable->GetAllSocketNames();
	Poseable->SetBoneLocationByName("Bone", Direction * Length, EBoneSpaces::ComponentSpace);

	float gap = Gap;

	for (FName name : allName)
	{
		if (name == "Armature") continue;

		FVector pos = subDir * Length;

		pos.Y -= gap;

		gap += Gap;

		Poseable->SetBoneLocationByName(name, pos, EBoneSpaces::ComponentSpace);

		subDir = SubRotate.RotateVector(subDir);

	}

}

