#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStatusComponent.generated.h"


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


public:
	FORCEINLINE float GetStrength() { return Strength; }
	FORCEINLINE float GetDexterity() { return Dexterity; }
	FORCEINLINE float GetVitality() { return Vitality; }
	FORCEINLINE float GetEnergy() { return Energy; }

	bool GetCriticalChance();

	void AddSkillBuff(class CSkill* InSkill);
	void AddItemBuff(class CItem* InItem);

protected:
	virtual void BeginPlay() override;

	TArray<class CSkill*> AddSkills;
	TArray<class CItemAsset*> AddItems;
};
