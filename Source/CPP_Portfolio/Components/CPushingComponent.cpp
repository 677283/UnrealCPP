#include "CPushingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

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
		offset = offset.RotateAngleAxis(-10, FVector::UpVector);
		offset *= PushingPower * GetScaledSphereRadius();
		actor->AddActorWorldOffset(offset);
		
	}
}

void UCPushingComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!character)
	{
		SetComponentTickEnabled(true);
	}
}