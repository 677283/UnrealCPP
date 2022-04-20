/*
	작성일 : 2022-04-15
	Sevarog 보스 스킬
	
	연습 : 다각형 안에 유닛이 있는지 체크를 할 수 있는가?

	TODO : 벽으로 쓸 에셋 찾기.
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

//스킬은 UObject를 상속 받아 따로 BeginPlay가 없으므로 오브젝트 생성시 호출로 초기화 해줍니다. 스킬의 Owner를 인자로 받습니다.
void UCSkill_Active_Fence::BeginPlay(ACharacter* InOwner)
{
	Super::BeginPlay(InOwner);

	//N각형 베이스 생성.
	CreateOrigin();
}

//스킬 사용 함수.
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

//스킬 주 처리 시작.
void UCSkill_Active_Fence::BeginDoSkill()
{
	Super::BeginDoSkill();

	ReadyCnt = 0; //생성 완료된 벽의 카운트를 세기 위한 변수 초기화.
	CreateWall();
}

//스킬 종료.
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

//모든 벽 생성 함수.
void UCSkill_Active_Fence::CreateWall()
{	
	WallVertecies.Reset(0);
	//기본 N각형 도형 꼭지점 복사. 복사 하며 150~500 사이즈로 랜덤하게 넓혀줍니다. (오목 다각형 만들기)
	for (FVector &ver : WallsOriginal)
		WallVertecies.Add(ver * UKismetMathLibrary::RandomFloatInRange(150, 500) + UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(),0)->GetActorLocation());
	
	//벽의 위치와 벽의 사이즈 설정 후 스폰 함수 콜.
	for (int i = 0; i < WallVertecies.Num(); i++)
	{
		FVector pos = (WallVertecies[i] + WallVertecies[(i + 1) % WallVertecies.Num()]) / 2; //중점.
		FVector dir = WallVertecies[i] - WallVertecies[(i + 1) % WallVertecies.Num()]; //회전을 위한 방향 벡터.
		float size = dir.Size() * 0.01f; //방향벡터 정규화시켜주기 전에 길이 * 0.01을 해주면 벽의 Y사이즈를 구할 수 있다.(1x1x1 큐브로 만들어진 벽이기에 가능)
		dir.Normalize();
		float flag = UKismetMathLibrary::Cross_VectorVector(FVector::RightVector, dir).Z < 0 ? -1 : 1; //회전값 왼, 오 정해주기.
		FRotator rot = FRotator(0, flag * UKismetMathLibrary::DegAcos(UKismetMathLibrary::Dot_VectorVector(FVector::RightVector, dir)), 0);//회전값 구하기.
		SpawnWall(pos, rot, size);
	}
}

//벽 생성 함수.
void UCSkill_Active_Fence::SpawnWall(const FVector &pos, const FRotator &rot, const float &size)//pos 벽의 위치, rot 벽의 회전 각, size 벽의 Y스케일
{
	ACActor_Fence_Wall* wall = OwnerCharacter->GetWorld()->SpawnActor<ACActor_Fence_Wall>(WallClass, pos, rot);
	wall->SetActorScale3D(FVector(0.1f, size, 1.0f));
	
	//벽은 밑에서 랜덤한 딜레이 후 랜덤 속도로 올라오고 일정 높이까지 올라온다면 Delegate로 알려줍니다.
	wall->OnReadyWall.BindUObject(this, &UCSkill_Active_Fence::ReadyCounting);
	Walls.Add(wall);
}

//N각형 베이스 생성 함수.
void UCSkill_Active_Fence::CreateOrigin()
{
	float angle = -360.0f / AngleCnt; //N각형의 꼭지점의 위치를 구하기 위해 회전 각.
	
	WallsOriginal.Reset(0);
	
	for (int i = 0; i < AngleCnt; i++)
		WallsOriginal.Add(FRotator(0.0f, angle * i, 0.0f).RotateVector(FVector::ForwardVector)); //반시계방향으로 꼭지점의 위치를 구한다.
}

//플레이어가 다각형 안에 있는지 체크하는 함수.
void UCSkill_Active_Fence::CheckLock()
{
	int cnt = 0, zero = 0;
	bool vertex = false;

	/*
		다각형 내부에있는지 체크를 하는법. 
		체크하고 싶은 유닛의 위치로부터 반직선 또는 일정길이의 선분을 그립니다. 그 선분과 다각형의 충돌을 체크하여 충돌되는 점이 짝수라면 외부. 홀수라면 내부 입니다.
		선분과 다각형의 충돌은 다각형의 모든 선분과 교차 하는지를 체크하고 있습니다.
		선분과 선분의 교차 체크 하는방법은 CCW 알고리즘을 이용하였습니다.
	*/
	FVector pos = OwnerCharacter->GetActorLocation();
	FVector dir = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * 10000;

	for (int i = 0; i < WallVertecies.Num(); i++)
	{
		//비교할 선분 2개의 점 4개를 인자로 보냅니다. 플레이어 위치, 플레이어 전방으로 일정 거리 위치, 다각형의 선분을 이루는 꼭지점 2개씩.
		//0은 꼭지점을 지나는것을 의미합니다. 꼭지점을 지난다면 앞에 선분 뒤에 선분 두번이 체크가 되므로 꼭지점을 지났을때를 체크합니다.
		switch (CheckCross(pos, dir, WallVertecies[i], WallVertecies[(i + 1) % WallVertecies.Num()]))
		{
		case 0:
			zero++;
		case 1:
			cnt++;
			break;
		}
	}

	//꼭지점 지난 횟수를 2로 나눈뒤 빼준다.
	cnt -= zero / 2;

	//다각형 내부일땐 즉사기.
	if (cnt % 2 != 0)
		UGameplayStatics::GetPlayerCharacter(OwnerCharacter->GetWorld(), 0)->TakeDamage(99999999, DamageEvent, OwnerCharacter->GetController(), OwnerCharacter);
}

//CCW 알고리즘
int32 UCSkill_Active_Fence::CCW(FVector a, FVector b, FVector c)
{
	int ans = (b.X - a.X) * (c.Y - a.Y) - (b.Y - a.Y)* (c.X - a.X);
	if (ans < 0) return 1;
	else if (ans > 0) return -1;
	else return 0;
}

//두개의 선분을 이루는 점 4개를 이용하여 체크하는 함수
int32 UCSkill_Active_Fence::CheckCross(FVector a, FVector b, FVector c, FVector d)
{
	int32 flag1 = CCW(a, b, c), flag2 = CCW(a, b, d), flag3 = CCW(c, d, a), flag4 = CCW(c, d, b);
	
	//선분과 교차했을때.
	if (flag1 * flag2 <= 0 && flag3 * flag4 <= 0)
	{
		//선분의 끝에서 교차했을땐 0을 리턴. 꼭지점을 지났다는것.
		if (flag1 * flag2 == 0 || flag3 * flag4 == 0)
			return 0;
		else
			return 1;
	}
	else 
		return 2;
}

//모든 벽이 특정 높이까지 올라왔을때마다 카운팅. 모든 벽이 올라왔을때 내부에 있는지 체크.
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