/*
	�ۼ��� : 2022-03-24
	���� ������ �ĳ��� ��� ������Ʈ.

	���� : �׼� ���ӿ��� �и��� ��� �����ұ�?

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

//�и��� SphereComponent�� ��� �޾� OnComponentBeginOverlap Delegate�� �����մϴ�.
void UCParryingComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	SetCollisionProfileName("Parrying");
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnComponentBeginOverlap.AddDynamic(this, &UCParryingComponent::OnBeginOverlap);
}

//�и� Ű �Է½� ���� �Լ�
void UCParryingComponent::DoParry()
{
	//Idle�����϶��� ����.
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());
	CheckFalse(state->IsStateIdle());

	//�������� ��� ����ϴ� EquipComponent
	UCEquipComponent* equip = CHelpers::GetComponent<UCEquipComponent>(GetOwner());

	//Ư�� ���⸸ �����ϹǷ� ������ ���� üũ
	if (NeedWeapons.Num() > 0)
	{
		int32 typeSum = 0;
		int32 weaponType = (int32)(equip->GetWeapon()->GetWeaponType());

		//���� Ÿ�� Enum���� 0~N���� �����ϹǷ� 2�� ������ �̿��Ͽ� �� �����ش�.
		for (EWeaponType type : NeedWeapons)
		{
			typeSum += pow(2, (int32)type);
		}

		//Or��Ʈ ������ �̿��� 0��� �Լ� ����.
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

//�и��� Ÿ�ֿ̹� �°� �浹ü  On, Off
void UCParryingComponent::OnCollision()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void UCParryingComponent::OffCollision()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//�и� �浹ü�� ���Ⱑ �ε������� ����.
void UCParryingComponent::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CLog::Log("parryingEnter");
	ACEquipActor* weapon = Cast<ACEquipActor>(OtherActor);
	//�浹ü�� ���Ⱑ �ƴϸ� �ƿ�.
	CheckNull(weapon);
	CheckTrue(OtherActor->GetOwner() == OwnerCharacter);
	

	FVector ownerForwardVector = OwnerCharacter->GetActorForwardVector();
	FVector actorLookVector = OtherActor->GetOwner()->GetActorLocation() - OwnerCharacter->GetActorLocation();
	actorLookVector.Normalize();

	//������ ���� �������ȿ����� �и��� �����մϴ�.
	float dot = UKismetMathLibrary::Dot_VectorVector(ownerForwardVector, actorLookVector);

	CheckTrue(dot < 0.3f);

	OtherActor->GetOwner()->TakeDamage(0, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	
}
