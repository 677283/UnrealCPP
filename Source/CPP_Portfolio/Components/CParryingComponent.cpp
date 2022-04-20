/*
	작성일 : 2022-03-24
	적의 공격을 쳐내는 기술 컴포넌트.

	연습 : 액션 게임에서 패링은 어떻게 구현할까?

*/

#include "CParryingComponent.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Components/CStateComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipActor.h"
#include "GameFramework/Character.h"


UCParryingComponent::UCParryingComponent()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//패링은 SphereComponent를 상속 받아 OnComponentBeginOverlap Delegate가 존재합니다.
void UCParryingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SetCollisionProfileName("Parrying");
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnComponentBeginOverlap.AddDynamic(this, &UCParryingComponent::OnBeginOverlap);
}

//패링 키 입력시 실행 함수
void UCParryingComponent::DoParry()
{
	//Idle상태일때만 가능.
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	CheckFalse(state->IsStateIdle());

	//장착중인 장비를 담당하는 EquipComponent
	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());

	//특정 무기만 가능하므로 가능한 무기 체크
	if (NeedWeapons.Num() > 0)
	{
		int32 typeSum = 0;
		int32 weaponType = (int32)(equip->GetWeapon()->GetWeaponType());

		//무기 타입 Enum문은 0~N까지 존재하므로 2의 제곱에 이용하여 다 더해준다.
		for (EWeaponType type : NeedWeapons)
		{
			typeSum += pow(2, (int32)type);
		}

		//Or비트 연산을 이용해 0라면 함수 종료.
		if (!(typeSum | weaponType))
			return;
	}
	
	state->SetStateAction();
	OwnerCharacter->PlayAnimMontage(ParryingMontage);

}

void UCParryingComponent::EndDoParry()
{
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	state->SetStateIdle();
}

//패링의 타이밍에 맞게 충돌체  On, Off
void UCParryingComponent::OnCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UCParryingComponent::OffCollision()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//패링 충돌체에 무기가 부딪혔을시 성공.
void UCParryingComponent::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CLog::Log("parryingEnter");
	ACEquipActor* weapon = Cast<ACEquipActor>(OtherActor);
	//충돌체가 무기가 아니면 아웃.
	CheckNull(weapon);
	CheckTrue(OtherActor->GetOwner() == OwnerCharacter);
	

	FVector ownerForwardVector = OwnerCharacter->GetActorForwardVector();
	FVector actorLookVector = OtherActor->GetOwner()->GetActorLocation() - OwnerCharacter->GetActorLocation();
	actorLookVector.Normalize();

	//내적을 통해 일정각안에서만 패링이 가능합니다.
	float dot = UKismetMathLibrary::Dot_VectorVector(ownerForwardVector, actorLookVector);

	CheckTrue(dot < 0.3f);

	OtherActor->GetOwner()->TakeDamage(0, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	
}
