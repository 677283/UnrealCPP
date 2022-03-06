#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Item/CItemStructures.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CParryingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CPP_PORTFOLIO_API UCParryingComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UCParryingComponent();

private:
	UPROPERTY(EditDefaultsOnly)
		FCustomDamageEvent DamageEvent;

	UPROPERTY(EditDefaultsOnly)
		class UAnimMontage* ParryingMontage;

	UPROPERTY(EditDefaultsOnly)
		TArray<EWeaponType> NeedWeapons;

protected:
	virtual void BeginPlay() override;

public:
	void DoParry();
	void EndDoParry();

public:
	void OnCollision();
	void OffCollision();

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	class ACharacter* OwnerCharacter;
};
