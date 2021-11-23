#include "Player/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/CSkillComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Item/Equip/Weapon/CWeaponAsset.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CDoAction.h"
#include "Skill/Active/Dual_Slash/CSkill_Active_Slash.h"
#include "Rendering/SkeletalMeshRenderData.h"

#define ACPlayer_DEBUG

ACPlayer::ACPlayer()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UCSkillComponent>(this, &Skill, "Skill");

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;


	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Inquisitor/Meshes/Gideon_Inquisitor.Gideon_Inquisitor'");
	
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/__ProjectFile/Player/Animation/ABP_CPlayer.ABP_CPlayer_C'");

	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0, -90, 0)));
	GetMesh()->SetAnimInstanceClass(animInstance);
	

	GetCapsuleComponent()->SetCollisionProfileName("Player");

	CHelpers::GetAsset(&Weapon_Dual, "CWeaponAsset'/Game/__ProjectFile/Items/Equip/Weapon/Dual_Silver/Dual_Silver.Dual_Silver'");

	CHelpers::GetClass<UCSkill>(&SlashClass, "Blueprint'/Game/__ProjectFile/Skills/Dual_Slash/BP_CSkill_Active_Slash.BP_CSkill_Active_Slash_C'");
	CHelpers::GetClass<UCSkill>(&ThrowClass, "Blueprint'/Game/__ProjectFile/Skills/Dual_Throw/BP_CSkill_Active_Throw.BP_CSkill_Active_Throw_C'");
	
	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon_Dual->BeginPlay(this);
	Weapon_Dual->GetEquipment()->OffHands();

	Equip->EquipItem(Weapon_Dual);

	Slash = NewObject<UCSkill>(this, SlashClass);
	Slash->BeginPlay(this);
	Skill->AddSkill(Slash);

	Throw = NewObject<UCSkill>(this, ThrowClass);
	Throw->BeginPlay(this);
	Skill->AddSkill(Throw);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalMouse", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalMouse", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::Sprint_Pressed);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::Sprint_Released);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::Sprint_Released);
	PlayerInputComponent->BindAction("EquipWeapon_1", EInputEvent::IE_Pressed, this, &ACPlayer::Equip_Weapon);
	PlayerInputComponent->BindAction("BasicAttack", EInputEvent::IE_Pressed, this, &ACPlayer::BasicAttack);
	PlayerInputComponent->BindAction("Skill_1", EInputEvent::IE_Pressed, this, &ACPlayer::Skill_1);
	PlayerInputComponent->BindAction("Skill_2", EInputEvent::IE_Pressed, this, &ACPlayer::Skill_2);

	//델리게이트를 이용해서 키 바인딩에 데이터 보내는 방법. 델리게이트 만들어준뒤 Template 이용
	/*PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::Sprint_Pressed, 1);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Released, this, &ACPlayer::Sprint_Released, 2);*/
}

void ACPlayer::Sprint_Pressed()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACPlayer::Sprint_Released()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ACPlayer::Equip_Weapon()
{
	//Equip->EquipItem(Weapon_Dual);
	Equip->GetWeapon()->GetEquipment()->ToggleHands();
}

void ACPlayer::BasicAttack(FKey InKey)
{
	Equip->GetWeapon()->Do_Action(this, InKey);
}

void ACPlayer::Skill_1()
{
	Throw->DoSkill();
	//Slash->DoSkill();
}

void ACPlayer::Skill_2()
{
	//Throw->DoSkill();
	Slash->DoSkill();
}

void ACPlayer::OnMoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}
void ACPlayer::OnMoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}
void ACPlayer::OnHorizontalLook(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}
void ACPlayer::OnVerticalLook(float AxisValue)
{
	CheckTrue(UKismetMathLibrary::NearlyEqual_FloatFloat(AxisValue, 0));
	if (AxisValue < 0)
	{
		if (GetControlRotation().Pitch > 40 && GetControlRotation().Pitch < 180)
			return;
	}
	else
	{
		if (GetControlRotation().Pitch < 320 && GetControlRotation().Pitch > 180)
			return;
	}

	AddControllerPitchInput(AxisValue * MouseSensitivity);
}