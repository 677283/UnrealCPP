#include "Player/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CEquipComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Equip/Weapon/CWeaponAsset.h"
#include "Items/Equip/Weapon/CEquipment.h"
#include "Items/Equip/Weapon/CDoAction.h"
#include "Skill/Active/Dual_Slash/CSkill_Active_Slash.h"

#define ACPlayer_DEBUG
//Test
ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetRootComponent());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	SpringArm->SetRelativeLocation(FVector(0, 0, 60));
	SpringArm->TargetArmLength = 300;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	USkeletalMesh* mesh;
	CHelpers::GetAsset(&mesh, "SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Inquisitor/Meshes/Gideon_Inquisitor.Gideon_Inquisitor'");
	
	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/__ProjectFile/Player/Animation/ABP_CPlayer.ABP_CPlayer_C'");

	GetMesh()->SetSkeletalMesh(mesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
	GetMesh()->SetRelativeRotation(FQuat(FRotator(0, -90, 0)));
	GetMesh()->SetAnimInstanceClass(animInstance);
	

	GetCapsuleComponent()->SetCollisionProfileName("Player");

	CHelpers::GetAsset(&Weapon_Dual, "CWeaponAsset'/Game/__ProjectFile/Items/Equip/Weapon/Dual_Silver.Dual_Silver'");
	
	
}

#pragma region UnrealOverride

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Weapon_Dual->BeginPlay(this);
	Weapon_Dual->GetEquipment()->OffHands();

	Equip->EquipItem(Weapon_Dual);
	Slash = NewObject<UCSkill_Active_Slash>(this, SlashClass);
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

	//델리게이트를 이용해서 키 바인딩에 데이터 보내는 방법. 델리게이트 만들어준뒤 Template 이용
	/*PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::Sprint_Pressed, 1);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Released, this, &ACPlayer::Sprint_Released, 2);*/
}

#pragma endregion

#pragma region Function

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
	Equip->GetWeapon()->GetDoAction()->DoAction(InKey);
}

#pragma region MoveInput
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
#pragma endregion

#pragma endregion