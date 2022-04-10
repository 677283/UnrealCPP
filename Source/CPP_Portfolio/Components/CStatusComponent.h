#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStatusComponent();

private:
	//데미지
	UPROPERTY(EditDefaultsOnly)
		float Strength = 0;
	
	//명중률, 크리
	UPROPERTY(EditDefaultsOnly)
		float Dexterity = 0;
	//라이프
	UPROPERTY(EditDefaultsOnly)
		float Vitality = 0;
	//마나
	UPROPERTY(EditDefaultsOnly)
		float Energy = 0;
	

	UPROPERTY(EditDefaultsOnly)
		float Life = 0;
		float CurrentLife;
	UPROPERTY(EditDefaultsOnly)
		float Mana = 0;
		float CurrentMana;

	UPROPERTY(EditDefaultsOnly)
		float Critical = 0;

	UPROPERTY(EditDefaultsOnly)
		float EndureTime = 0;

protected:
	virtual void BeginPlay() override;

public:
	bool GetCriticalChance();
	float SetLife(float InValue);
	void Hitted();
	void CheckEndureTimer();

	FORCEINLINE float GetStrength() { return Strength; }
	FORCEINLINE float GetDexterity() { return Dexterity; }
	FORCEINLINE float GetVitality() { return Vitality; }
	FORCEINLINE float GetEnergy() { return Energy; }
	FORCEINLINE void  OnSuperArmor() { bSuperAmor = true; }
	FORCEINLINE void  OffSuperArmor() { bSuperAmor = false; }
	FORCEINLINE bool  IsHitable() { return bHitable && !bSuperAmor; }
	
private:
	TArray<class CSkill*> BuffSkills;
	TArray<class CItemAsset*> BuffItems;

public:
	FOnDeath OnDeath;
	bool bHitable = true;
	bool bSuperAmor = false;
	float CheckEndureTime = 0.0f;
	FTimerHandle EndureTimerHandle;
};
