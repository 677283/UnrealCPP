#include "CPushingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"


#define PUSHINCOMPONENT_DEBUG

UCPushingComponent::UCPushingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	OnComponentBeginOverlap.AddDynamic(this, &UCPushingComponent::OnBeginOverlap);
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

	TArray<AActor*> hits;
	GetOverlappingActors(hits, ACEnemy::StaticClass());
	hits.Remove(OwnerCharacter);

	if (hits.Num() <= 0)	
	{
		SetComponentTickEnabled(false);
		return;
	}
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	for (AActor* actor : hits)
	{
		FVector offset = actor->GetActorLocation() - GetComponentLocation();
		offset.Normalize();
		offset *= PushingPower * GetScaledSphereRadius();
		actor->AddActorWorldOffset(offset);
		if (!!player)
		{
			FRotator rotator = UKismetMathLibrary::FindLookAtRotation(actor->GetActorLocation(), OwnerCharacter->GetActorLocation());
			actor->SetActorRotation(rotator);
		}
	}
/*
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
*/
}

void UCPushingComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!OtherActor)
	{
		SetComponentTickEnabled(true);
		/*FVector offset = character->GetActorLocation() - GetComponentLocation();
		offset.Normalize();
		offset *= PushingPower * Radius;
		character->AddActorWorldOffset(offset);*/
	}
}