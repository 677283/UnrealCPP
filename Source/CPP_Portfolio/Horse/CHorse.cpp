#include "Horse/CHorse.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Player/CPlayer.h"

ACHorse::ACHorse()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetRelativeLocation(FVector(-60, 0, -70));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->SocketOffset = FVector(0, 60, 0);

	UShapeComponent* collision = CHelpers::GetComponent<UShapeComponent>(this);

	collision->OnComponentBeginOverlap.AddDynamic(this, &ACHorse::OnComponentBeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &ACHorse::OnComponentEndOverlap);
}

void ACHorse::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACHorse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACHorse::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACHorse::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACHorse::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalMouse", this, &ACHorse::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalMouse", this, &ACHorse::OnVerticalLook);
}

void ACHorse::OnMoveForward(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}
void ACHorse::OnMoveRight(float AxisValue)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}
void ACHorse::OnHorizontalLook(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}
void ACHorse::OnVerticalLook(float AxisValue)
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

	AddControllerPitchInput(AxisValue);
}

void ACHorse::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	CLog::Log("In");
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckFalse(OtherActor == player);

	player->OnRideWidget(this);
}

void ACHorse::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CLog::Log("Out");
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CheckFalse(OtherActor == player);

	player->OffRideWidget();
}