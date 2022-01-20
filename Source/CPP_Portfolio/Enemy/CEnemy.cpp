#include "CEnemy.h"
#include "Global.h"
#include "Components/CEquipComponent.h"
#include "Item/Equip/Weapon/CWeaponItem.h"

ACEnemy::ACEnemy()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/SK_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'");
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/ABP_CCharacter.ABP_CCharacter_C'");

	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetAnimInstanceClass(animInstance);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACEnemy::Attack()
{
	//FKey key("LeftMouseButton");
	Equip->GetWeapon()->Do_Action(this, FKey("LeftMouseButton"));
}
