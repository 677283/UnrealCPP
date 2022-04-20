/*
	�ۼ��� : 2022-04-15
	Sevarog ���� ��ų
	
	���� : �ٰ��� �ȿ� ������ �ִ��� üũ�� �� �� �ִ°�?

	TODO : ������ �� ���� ã��.
*/
#include "CSkill_Active_Fence.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"
#include "Skill/Active/Sevarog_Fence/CActor_Fence_Wall.h"
#include "Enemy/AI/CEnemy_AI_Boss.h"

UCSkill_Active_Fence::UCSkill_Active_Fence()
{
	
}

//��ų�� UObject�� ��� �޾� ���� BeginPlay�� �����Ƿ� ������Ʈ ������ ȣ��� �ʱ�ȭ ���ݴϴ�. ��ų�� Owner�� ���ڷ� �޽��ϴ�.
void UCSkill_Active_Fence::BeginPlay(ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	//N���� ���̽� ����.
	CreateOrigin();
}

//��ų ��� �Լ�.
void UCSkill_Active_Fence::DoSkill()
{
	Super::DoSkill();

	CheckFalse(State->IsStateIdle());
	
	State->SetStateSkill();
	if (!!Montage)
		OwnerCharacter->PlayAnimMontage(Montage);
	ReadyCnt = 0;
	CreateWall();
}

//��ų �� ó�� ����.
void UCSkill_Active_Fence::BeginDoSkill()
{
	Super::BeginDoSkill();

	ReadyCnt = 0; //���� �Ϸ�� ���� ī��Ʈ�� ���� ���� ���� �ʱ�ȭ.
	CreateWall();
}

//��ų ����.
void UCSkill_Active_Fence::EndDoSkill()
{
	Super::EndDoSkill();
	
	ACEnemy_AI_Boss* boss = Cast<ACEnemy_AI_Boss>(OwnerCharacter);
	if (!!boss)
	{
		boss->FinishPattern();
		CLog::Log("ENDSKILL");
	}

	State->SetStateIdle();
}

//��� �� ���� �Լ�.
void UCSkill_Active_Fence::CreateWall()
{	
	WallVertecies.Reset(0);
	//�⺻ N���� ���� ������ ����. ���� �ϸ� 150~500 ������� �����ϰ� �����ݴϴ�. (���� �ٰ��� �����)
	for (FVector &ver : WallsOriginal)
		WallVertecies.Add(ver * UKismetMathLibrary::RandomFloatInRange(150, 500) + UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(),0)->GetActorLocation());
	
	//���� ��ġ�� ���� ������ ���� �� ���� �Լ� ��.
	for (int i = 0; i < WallVertecies.Num(); i++)
	{
		FVector pos = (WallVertecies[i] + WallVertecies[(i + 1) % WallVertecies.Num()]) / 2; //����.
		FVector dir = WallVertecies[i] - WallVertecies[(i + 1) % WallVertecies.Num()]; //ȸ���� ���� ���� ����.
		float size = dir.Size() * 0.01f; //���⺤�� ����ȭ�����ֱ� ���� ���� * 0.01�� ���ָ� ���� Y����� ���� �� �ִ�.(1x1x1 ť��� ������� ���̱⿡ ����)
		dir.Normalize();
		float flag = UKismetMathLibrary::Cross_VectorVector(FVector::RightVector, dir).Z < 0 ? -1 : 1; //ȸ���� ��, �� �����ֱ�.
		FRotator rot = FRotator(0, flag * UKismetMathLibrary::DegAcos(UKismetMathLibrary::Dot_VectorVector(FVector::RightVector, dir)), 0);//ȸ���� ���ϱ�.
		SpawnWall(pos, rot, size);
	}
}

//�� ���� �Լ�.
void UCSkill_Active_Fence::SpawnWall(const FVector &pos, const FRotator &rot, const float &size)//pos ���� ��ġ, rot ���� ȸ�� ��, size ���� Y������
{
	ACActor_Fence_Wall* wall = OwnerCharacter->GetWorld()->SpawnActor<ACActor_Fence_Wall>(WallClass, pos, rot);
	wall->SetActorScale3D(FVector(0.1f, size, 1.0f));
	
	//���� �ؿ��� ������ ������ �� ���� �ӵ��� �ö���� ���� ���̱��� �ö�´ٸ� Delegate�� �˷��ݴϴ�.
	wall->OnReadyWall.BindUObject(this, &UCSkill_Active_Fence::ReadyCounting);
	Walls.Add(wall);
}

//N���� ���̽� ���� �Լ�.
void UCSkill_Active_Fence::CreateOrigin()
{
	float angle = -360.0f / AngleCnt; //N������ �������� ��ġ�� ���ϱ� ���� ȸ�� ��.
	
	WallsOriginal.Reset(0);
	
	for (int i = 0; i < AngleCnt; i++)
		WallsOriginal.Add(FRotator(0.0f, angle * i, 0.0f).RotateVector(FVector::ForwardVector)); //�ݽð�������� �������� ��ġ�� ���Ѵ�.
}

//�÷��̾ �ٰ��� �ȿ� �ִ��� üũ�ϴ� �Լ�.
void UCSkill_Active_Fence::CheckLock()
{
	int cnt = 0, zero = 0;
	bool vertex = false;

	/*
		�ٰ��� ���ο��ִ��� üũ�� �ϴ¹�. 
		üũ�ϰ� ���� ������ ��ġ�κ��� ������ �Ǵ� ���������� ������ �׸��ϴ�. �� ���а� �ٰ����� �浹�� üũ�Ͽ� �浹�Ǵ� ���� ¦����� �ܺ�. Ȧ����� ���� �Դϴ�.
		���а� �ٰ����� �浹�� �ٰ����� ��� ���а� ���� �ϴ����� üũ�ϰ� �ֽ��ϴ�.
		���а� ������ ���� üũ �ϴ¹���� CCW �˰����� �̿��Ͽ����ϴ�.
	*/
	FVector pos = OwnerCharacter->GetActorLocation();
	FVector dir = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 10000;

	for (int i = 0; i < WallVertecies.Num(); i++)
	{
		//���� ���� 2���� �� 4���� ���ڷ� �����ϴ�. �÷��̾� ��ġ, �÷��̾� �������� ���� �Ÿ� ��ġ, �ٰ����� ������ �̷�� ������ 2����.
		//0�� �������� �����°��� �ǹ��մϴ�. �������� �����ٸ� �տ� ���� �ڿ� ���� �ι��� üũ�� �ǹǷ� �������� ���������� üũ�մϴ�.
		switch (CheckCross(pos, dir, WallVertecies[i], WallVertecies[(i + 1) % WallVertecies.Num()]))
		{
		case 0:
			zero++;
		case 1:
			cnt++;
			break;
		}
	}

	//������ ���� Ƚ���� 2�� ������ ���ش�.
	cnt -= zero / 2;

	//�ٰ��� �����϶� ����.
	if (cnt % 2 != 0)
		UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->TakeDamage(99999999, DamageEvent, OwnerCharacter->GetController(), OwnerCharacter);
}

//CCW �˰���
int32 UCSkill_Active_Fence::CCW(FVector a, FVector b, FVector c)
{
	int ans = (b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y)* (c.X - a.X);
	if (ans < 0) return 1;
	else if (ans > 0) return -1;
	else return 0;
}

//�ΰ��� ������ �̷�� �� 4���� �̿��Ͽ� üũ�ϴ� �Լ�
int32 UCSkill_Active_Fence::CheckCross(FVector a, FVector b, FVector c, FVector d)
{
	int32 flag1 = CCW(a, b, c), flag2 = CCW(a, b, d), flag3 = CCW(c, d, a), flag4 = CCW(c, d, b);
	
	//���а� ����������.
	if (flag1 * flag2 <= 0 && flag3 * flag4 <= 0)
	{
		//������ ������ ���������� 0�� ����. �������� �����ٴ°�.
		if (flag1 * flag2 == 0 || flag3 * flag4 == 0)
			return 0;
		else
			return 1;
	}
	else 
		return 2;
}

//��� ���� Ư�� ���̱��� �ö���������� ī����. ��� ���� �ö������ ���ο� �ִ��� üũ.
void UCSkill_Active_Fence::ReadyCounting()
{
	ReadyCnt++;

	if (ReadyCnt == AngleCnt)
	{
		CheckLock();
		FTimerHandle handle;
		for (int i = 0; i < Walls.Num(); i++)
			Walls[i]->Destroy();
		OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([=]()
		{
			
		}), 1.0f, false);
		Walls.Reset(0);
		EndDoSkill();
	}

}