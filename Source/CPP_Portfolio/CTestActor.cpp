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

	if (FMath::IsNearlyZero(Gap))
		Gap = Poseable->GetBoneLocation("Bone", EBoneSpaces::ComponentSpace).Y;

	AllName = Poseable->GetAllSocketNames();
	AllName.Remove("Armature");
	AllName.Remove("Bone");

	Poseable->SetBoneLocationByName(AllName[5], Poseable->GetBoneLocation(AllName[5]) * 3, EBoneSpaces::ComponentSpace);
}

void ACTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector subDir;

	//Direction = Rotate.RotateVector(Direction);

	//subDir = Direction;

	//Poseable->SetBoneLocationByName("Bone", Direction * Length, EBoneSpaces::ComponentSpace);

	//float subGap = Gap;

	//for (FName name : AllName)
	//{
	//	subDir = SubRotate.RotateVector(subDir);
	//	
	//	FVector pos = subDir * Length;

	//	pos.Y -= subGap;

	//	subGap += Gap;

	//	Poseable->SetBoneLocationByName(name, pos, EBoneSpaces::ComponentSpace);

	//}

}

