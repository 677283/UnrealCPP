#include "CPushingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"


#define PUSHINCOMPONENT_DEBUG

UCPushingComponent::UCPushingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCPushingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SetCollisionProfileName("Pushing");
}

void UCPushingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), GetComponentLocation(), GetComponentLocation(), Radius, "Pushing", false, ignoreActors, DrawDebugType, hitResults, true);

	if (hitResults.Num() <= 0)
	{
		SetComponentTickEnabled(false);
		return;
	}

	for (FHitResult hitResult : hitResults)
	{
		if (hitResult.Actor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
			continue;
		FVector offset = hitResult.Actor->GetActorLocation() - GetComponentLocation();
		offset.Normalize();
		offset *= PushingPower * Radius;
		hitResult.Actor->AddActorWorldOffset(offset);
	}


}

