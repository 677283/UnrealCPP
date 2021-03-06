#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/CEnemy_AI.h"
#include "CEnemy_AI_Boss.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACEnemy_AI_Boss : public ACEnemy_AI
{
	GENERATED_BODY()

public:
	void Boss_Attack();

private:
	UPROPERTY(EditDefaultsOnly)
		class UMaterialInstanceConstant* DisMatConst;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCSkill_Active_Subjugate> SubjugateClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCSkill_Active_SpawnClone> SpawnCloneClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCSkill_Active_Fence> FenceClass;
	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* DashMontage;
	UPROPERTY(EditDefaultsOnly)
		float DissolveP;
	UPROPERTY(EditDefaultsOnly)
		class UNiagaraSystem* DashEffect;

protected:
	virtual void BeginPlay() override;

public:
	void Hidding();
	UFUNCTION(BlueprintCallable)
	void CastSubjugate();
	UFUNCTION(BlueprintCallable)
	void Dash();
	void EndDash();
	void CastFence();
	void ChangeMat(bool flag);
	void DisTimer();

	FORCEINLINE bool IsPattern() { return bIsPattern; }
	FORCEINLINE void StartPattern() { bIsPattern = true; }
	FORCEINLINE void FinishPattern() { bIsPattern = false; }
private:
	UPROPERTY()
	TArray<class UMaterialInterface*> OriMaterials;
	bool bIsPattern = true;
	class UCSkill_Active_Subjugate* Subjugate;
	class UCSkill_Active_SpawnClone* SpawnClone;
	class UCSkill_Active_Fence* Fence;
	
	FTimerHandle DisHandle;
	
	UPROPERTY()
		class UMaterialInstanceDynamic* DisMatDynamic;
	float DissolvePower = 0;
};
