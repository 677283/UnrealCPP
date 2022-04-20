/*
	�ۼ��� : 2022-04-02
	���ֳ��� �а� ���� �� �ְ� �����ص� ������Ʈ.

	���� : ���� ���� ���ֳ��� �ѷ� ���̸� �������� ��� �ذ��Ұ��ΰ�?
*/

#include "CPushingComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Enemy/CEnemy.h"
#include "Player/CPlayer.h"

//UCPushingComponent�� SphereComponent�� ��� �ް� �־� OnComponentBeginOverlap�� ���� �ֽ��ϴ�.
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

	//�浹�� ������ ���ٸ� Tick�� ���ֵ��� �Ѵ�.
	if (hits.Num() <= 0)	
	{
		SetComponentTickEnabled(false);
		return;
	}

	//ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	//�浹�� ������ �ٶ󺸴� ���� �ڷ� �о��ֵ��� �Ѵ�.
	for (AActor* actor : hits)
	{
		FVector offset = actor->GetActorLocation() - GetComponentLocation();
		offset.Normalize();
		offset = offset.RotateAngleAxis(-10, FVector::UpVector);
		offset *= PushingPower * GetScaledSphereRadius();
		actor->AddActorWorldOffset(offset);
	}
}

//�浹�Ǵ� ��ü�� ������ �ٽ� Tick�� ���ش�.
void UCPushingComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* character = Cast<ACharacter>(OtherActor);
	if (!!character)
	{
		SetComponentTickEnabled(true);
	}
}