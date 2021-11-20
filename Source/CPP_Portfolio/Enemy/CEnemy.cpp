#include "CEnemy.h"
#include "Global.h"

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