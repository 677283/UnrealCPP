#include "CTestActor.h"
#include "Global.h"
#include "Components/PoseableMeshComponent.h"

ACTestActor::ACTestActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ACTestActor::BeginPlay()
{
	Super::BeginPlay();

	int32 flag = 0;
	CLog::Log(flag);
	FTimerHandle handle;

	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([&]()
	{
		CLog::Log("Enter");
		flag++;
		CLog::Log(flag);
	}), 3,false);
	CLog::Log("Out");
}

void ACTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

