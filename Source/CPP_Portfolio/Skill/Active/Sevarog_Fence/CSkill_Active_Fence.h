#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "Item/CItemStructures.h"
#include "CSkill_Active_Fence.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_Fence : public UCSkill_Active
{
	GENERATED_BODY()
	
public:
	UCSkill_Active_Fence();

private:
	struct WallVertex
	{
		public :
			WallVertex()
			{
				Point_1 = FVector::ZeroVector;
				Point_2 = FVector::ZeroVector;
			}
			WallVertex(FVector point_1, FVector point_2)
			{
				Point_1 = point_1;
				Point_2 = point_2;
			};
			FVector Point_1;
			FVector Point_2;
	};

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class ACActor_Fence_Wall> WallClass;
	UPROPERTY(EditDefaultsOnly)
		int32 AngleCnt;
	UPROPERTY(EditDefaultsOnly)
		FCustomDamageEvent DamageEvent;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

private:
	void CreateWall();
	void SpawnWall(const FVector &pos, const FRotator &rot, const float &size);
	void CreateOrigin();
	void CheckLock();
	int32 CCW(FVector a, FVector b, FVector c);
	int32 CheckCross(FVector a, FVector b, FVector c, FVector d);
	void ReadyCounting();

private:
	FVector StartPosition;
	TArray<FVector>WallsOriginal;
	int32 ReadyCnt;
	TArray<FVector> WallVertecies;
	TArray<class ACActor_Fence_Wall*> Walls;
};
