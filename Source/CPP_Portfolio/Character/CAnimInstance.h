#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "CAnimInstance.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Speed;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CharacterMovement")
		float Direction;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapon")
		EWeaponType WeaponType = EWeaponType::Max;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Riding")
		bool bRiding;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bJumping;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		bool bSecondJump;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACCharacter* OwnerCharacter;
	class UCEquipComponent* Equip;
	class UCRidingComponent* Riding;
	class UNavMovementComponent* Movement;

	FRotator LastRotate;


};
