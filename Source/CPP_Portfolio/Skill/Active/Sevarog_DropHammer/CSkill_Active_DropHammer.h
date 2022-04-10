#pragma once

#include "CoreMinimal.h"
#include "Skill/Active/CSkill_Active.h"
#include "CSkill_Active_DropHammer.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCSkill_Active_DropHammer : public UCSkill_Active
{
	GENERATED_BODY()
		
public:
	UCSkill_Active_DropHammer();

private:
	/*UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* Montage;*/

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> HammerCollisionCheck;

	UPROPERTY(EditDefaultsOnly)
		float Damage;

public:
	virtual void BeginPlay(class ACharacter* InOwner) override;
	virtual void DoSkill() override;
	virtual void BeginDoSkill() override;
	virtual void EndDoSkill() override;

	void OnCollision();
	void OffCollision();

	void OffCollisionTimer();

private:
	class USphereComponent* Collision;

	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
