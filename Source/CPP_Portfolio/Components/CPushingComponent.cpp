/*
	작성일 : 2022-04-02
	유닛끼리 밀고 나갈 수 있게 구현해둔 컴포넌트.

	연습 : 서로 적인 유닛끼리 둘러 쌓이면 갇힌것을 어떻게 해결할것인가?
*/

#include "CPushingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

//UCPushingComponent는 SphereComponent를 상속 받고 있어 OnComponentBeginOverlap를 갖고 있습니다.
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

	//충돌된 유닛이 없다면 Tick을 꺼주도록 한다.
	if (hits.Num() <= 0)	
	{
		SetComponentTickEnabled(false);
		return;
	}

	//ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	//충돌한 유닛은 바라보는 방향 뒤로 밀어주도록 한다.
	for (AActor* actor : hits)
	{
		FVector offset = actor->GetActorLocation() - GetComponentLocation();
		offset.Normalize();
		offset = offset.RotateAngleAxis(-10, FVector::UpVector);
		offset *= PushingPower * GetScaledSphereRadius();
		actor->AddActorWorldOffset(offset);
	}
}

//충돌되는 객체가 있을때 다시 Tick을 켜준다.
void UCPushingComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!character)
	{
		SetComponentTickEnabled(true);
	}
}