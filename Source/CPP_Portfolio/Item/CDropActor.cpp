#include "CDropActor.h"
#include "Global.h"
#include "Components/ShapeComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"

ACDropActor::ACDropActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root;
	
	CHelpers::CreateComponent<USceneComponent>(this, &root, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", root);

	//TODO Create TextRender
}

void ACDropActor::BeginPlay()
{
	Super::BeginPlay();
	
	Collision = CHelpers::GetComponent<UShapeComponent>(this);
	if (!!Collision)
		Collision->OnComponentBeginOverlap.AddDynamic(this, &ACDropActor::OnComponentBeginOverlap);
	GetComponents<UMeshComponent>(Meshes);
	PickUp();
}

void ACDropActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0, RotateSpeed * DeltaTime, 0));
	//TODO TextRender Billboard
}


//TODO TextRender SetVisibility
void ACDropActor::Drop(FVector InDropPosition)
{
	for (UMeshComponent* mesh : Meshes)
	{
		mesh->SetVisibility(true);
	}
	//Mesh->SetVisibility(true);
	SetActorTickEnabled(true);
	SetActorEnableCollision(true);


	TArray<AActor*> ignoreActors;

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), InDropPosition, InDropPosition + (FVector::UpVector * -300), ETraceTypeQuery::TraceTypeQuery1, false, ignoreActors, EDrawDebugTrace::None, hitResult, true);


	SetActorLocation(hitResult.ImpactPoint + DropOffset);
}

void ACDropActor::PickUp()
{
	for (UMeshComponent* mesh : Meshes)
	{
		mesh->SetVisibility(false);
	}
	//Mesh->SetVisibility(false);
	SetActorTickEnabled(false);
	SetActorEnableCollision(false);
}

void ACDropActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}