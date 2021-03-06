#include "Player/CPlayer.h"
#include "Global.h"

#include "CGameInstance.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/CSkillComponent.h"
#include "Components/CInventoryComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CRidingComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/CQuickSlotComponent.h"
#include "Components/CParryingComponent.h"

#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Item/Equip/Weapon/CDoAction.h"

#include "Horse/CHorse.h"
#include "Skill/Active/Dual_Slash/CSkill_Active_Slash.h"
#include "Skill/Passive/Rope/CSkill_Passive_Rope.h"

#include "Skill/Active/Sevarog_Fence/CSkill_Active_Fence.h"


#include "Widget/CWidget_PickUp.h"
#include "Widget/CWidget_Inventory.h"
#include "Widget/CWidget_Equip.h"
#include "Widget/CWidget_SkillTree.h"
#include "Widget/CWidget_QuickSlot.h"
#include "Widget/CWidget_Damage.h"
#include "Widget/CWidget_OnRide.h"
#include "Widget/CWidget_SkillTree_Tab.h"
#include "Widget/CWidget_HUD.h"

#include "NavigationSystem.h"
#include "NavigationPath.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACPlayer::ACPlayer()
{
	//Create Component
	{
		CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
		CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
		CHelpers::CreateActorComponent<UCInventoryComponent>(this, &Inventory, "Inventory");
		CHelpers::CreateComponent<USceneCaptureComponent2D>(this, &Capture, "Capture",GetRootComponent());
		CHelpers::CreateComponent<UCParryingComponent>(this, &Parrying, "Parrying", GetRootComponent());

		UTextureRenderTarget2D* texture;
		CHelpers::GetAsset(&texture, "TextureRenderTarget2D'/Game/__ProjectFile/Textures/EquipTargetTexutre.EquipTargetTexutre'");
		Capture->TextureTarget = texture;
		Capture->ShowFlags.Atmosphere = 0;
		Capture->bCaptureEveryFrame = false;
		Capture->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
		Capture->ShowFlags.Atmosphere = SFG_Transient;

		//EquipComponent - InventoryComponent Link
		Equip->OnEquip.BindUObject(Inventory, &UCInventoryComponent::OnEquip);
		Equip->OnUnequip.BindUObject(Inventory, &UCInventoryComponent::OnUnequip);
		Inventory->OnEquipInventory.BindUObject(Equip, &UCEquipComponent::EquipItem);


		//View Setting
		{
			bUseControllerRotationYaw = false;
			GetCharacterMovement()->bOrientRotationToMovement = true;
			GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		}

		//SpringArm Setting
		{
			SpringArm->SetRelativeLocation(FVector(0, 0, 140));
			SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
			SpringArm->TargetArmLength = 200;
			SpringArm->bDoCollisionTest = false;
			SpringArm->bUsePawnControlRotation = true;
			SpringArm->bEnableCameraLag = true;
			SpringArm->SocketOffset = FVector(0, 60, 0);
		}

		//Mesh Setting
		{
			USkeletalMesh* mesh;
			CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Inquisitor/Meshes/Gideon_Inquisitor.Gideon_Inquisitor'");

			TSubclassOf<UAnimInstance> animInstance;
			CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/__ProjectFile/Player/Animation/ABP_CPlayer.ABP_CPlayer_C'");
			
			GetMesh()->SetSkeletalMesh(mesh);
			GetMesh()->SetRelativeLocation(FVector(0, 0, -80));
			GetMesh()->SetRelativeRotation(FQuat(FRotator(0, -90, 0)));
			GetMesh()->SetAnimInstanceClass(animInstance);
		}

		//Collision Setting
		GetCapsuleComponent()->SetCollisionProfileName("Player");
		
		Movement = CHelpers::GetComponent<UCharacterMovementComponent>(this);
	}

	CHelpers::GetAsset(&DashMontage, "AnimMontage'/Game/AdventureAnimset/Animations/ExtremeLocomotion/Anim_Dash_Montage.Anim_Dash_Montage'");

	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Capture->ShowOnlyActors.Add(this);

	//Widget Initialize
	{
		if (!!PickUpWidgetClass)
		{
			PickUpWidget = CreateWidget<UCWidget_PickUp, APlayerController>(GetController<APlayerController>(), PickUpWidgetClass);
			PickUpWidget->AddToViewport();
			PickUpWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		if (!!RideWidgetClass)
		{
			RideWidget = CreateWidget<UCWidget_OnRide, APlayerController>(GetController<APlayerController>(), RideWidgetClass);
			RideWidget->AddToViewport();
			RideWidget->SetVisibility(ESlateVisibility::Hidden);
		}

		if (!!HUDClass)
		{
			HUD = CreateWidget<UCWidget_HUD, APlayerController>(GetController<APlayerController>(), HUDClass);
			Cast<UCGameInstance>(GetGameInstance())->SetHUD(HUD);
			HUD->AddToViewport();

			//Inventory Delegate Bind
			{
				UCWidget_Inventory* inventoryWidget = Cast<UCWidget_Inventory>(HUD->GetWidget("Inventory"));
				if (!!inventoryWidget)
				{
					inventoryWidget->OnZUpdate.BindUObject(HUD, &UCWidget_HUD::SetZOrder);
					inventoryWidget->OnUseItem.BindUObject(Inventory, &UCInventoryComponent::UseItem);
					inventoryWidget->OnSwapItem.BindUObject(Inventory, &UCInventoryComponent::SwapItem);

					inventoryWidget->OnUnequip_InvenWidget.BindUObject(Equip, &UCEquipComponent::UnequipItem);

					Inventory->OnAddItem.BindUObject(inventoryWidget, &UCWidget_Inventory::OnAddItem);
					Inventory->OnSlotUpdate.BindUObject(inventoryWidget, &UCWidget_Inventory::OnSlotUpdate);
				}
			}
			//Equip Delegate Bind
			{
				UCWidget_Equip* equipWidget = Cast<UCWidget_Equip>(HUD->GetWidget("Equip"));
				if (!!equipWidget)
				{
					equipWidget->OnZUpdate.BindUObject(HUD, &UCWidget_HUD::SetZOrder);
					equipWidget->OnEquip_EquipWidget.BindUObject(Equip, &UCEquipComponent::EquipItem);
					equipWidget->OnUnequip_EuipWidget.BindUObject(Equip, &UCEquipComponent::UnequipItem);

					Equip->OnEquipWidget.BindUObject(equipWidget, &UCWidget_Equip::OnEquipWidget);
				}
			}
			//SkillTree Delegate Bind
			{
				UCWidget_SkillTree* skillTreeWidget = Cast<UCWidget_SkillTree>(HUD->GetWidget("SkillTree"));
				if (!!skillTreeWidget)
				{
					skillTreeWidget->OnZUpdate.BindUObject(HUD, &UCWidget_HUD::SetZOrder);
				}
			}

			//QuickSlot
			{
				QuickSlotWidget = Cast<UCWidget_QuickSlot>(HUD->GetWidgetFromName("QuickSlot"));
			}
		}
	}

	//Basic Item Create
	{
		if (BaiscWeaponName.Len() > 0)
		{
			UCItem* basicWeapon = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->CreateItem(this, BaiscWeaponName);
			Inventory->AddItem(basicWeapon);
			Inventory->UseItem(basicWeapon);
		}
	}

	//TEST
	Rope = NewObject<UCSkill_Passive_Rope>(this, testclass);
	Skill->AddSkill(Rope);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State->IsStateAction())
	{
		FRotator actorRotator = GetActorRotation();
		FRotator controlRotator = GetControlRotation();

		actorRotator = UKismetMathLibrary::RInterpTo(actorRotator, controlRotator, DeltaTime, AttackRotatorSpeed);
		actorRotator.Pitch = 0;
		actorRotator.Roll = 0;
		SetActorRotation(actorRotator);
	}

	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, L"EStateType", true);
	if (!!enumPtr)
		CLog::Print(enumPtr->GetNameStringByIndex((int32)State->GetState()), 4, 0);
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
	PlayerInputComponent->BindAction("PickUp", EInputEvent::IE_Pressed, this, &ACPlayer::PickUp);
	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &ACPlayer::InventoryToggle);
	PlayerInputComponent->BindAction("SkillTree", EInputEvent::IE_Pressed, this, &ACPlayer::SkillTreeToggle);
	PlayerInputComponent->BindAction("EquipWidget", EInputEvent::IE_Pressed, this, &ACPlayer::EquipToggle);
	PlayerInputComponent->BindAction("OnDebug", EInputEvent::IE_Pressed, this, &ACPlayer::OnDebug);
	PlayerInputComponent->BindAction("Riding", EInputEvent::IE_Pressed, this, &ACPlayer::OnRiding);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACPlayer::OnJump);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_DoubleClick, this, &ACPlayer::OnDash);
	PlayerInputComponent->BindAction("SwapWeapon", EInputEvent::IE_Pressed, this, &ACPlayer::SwapWeapon);

	//???????????? ???????? ?? ???????? ?????? ?????? ????. ?????????? ?????????? Template ????
	/*PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::Sprint_Pressed, 1);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("Sprint", EInputEvent::IE_Released, this, &ACPlayer::Sprint_Released, 2);*/
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

//???? ??????
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
	CheckNull(Equip->GetWeapon());
	Equip->GetWeapon()->ToggleHands();
}

void ACPlayer::BasicAttack(FKey InKey)
{
	CheckNull(Equip->GetWeapon());
	Equip->GetWeapon()->Do_Action(this, InKey);
}

void ACPlayer::Skill_1()
{
	QuickSlotWidget->ActiveSlot(0);
}

void ACPlayer::Skill_2()
{
	//QuickSlotWidget->ActiveSlot(1);
	CheckNull(Parrying);
	Parrying->DoParry();
}

void ACPlayer::PickUp()
{
	CheckNull(CheckItem);
	
	CheckFalse(Inventory->AddItem(CheckItem));

	CheckItem = NULL;
}

void ACPlayer::SwapWeapon()
{
	CheckFalse(State->IsStateIdle());
	Equip->SwapWeapon();
}

void ACPlayer::SwapWeaponNotify()
{
	Equip->SwapWeapon();
}

void ACPlayer::InventoryToggle()
{
	HUD->ToggleWidget("Inventory");
}

void ACPlayer::SkillTreeToggle()
{
	HUD->ToggleWidget("SkillTree");
}

void ACPlayer::EquipToggle()
{
	HUD->ToggleWidget("Equip");
}

void ACPlayer::OnDebug()
{
	SetActorTickEnabled(!IsActorTickEnabled());
}

void ACPlayer::OnRiding()
{
	CheckNull(CheckHorse);
	CheckFalse(State->IsStateIdle());

	Riding->OnRide(CheckHorse);
}

void ACPlayer::OnJump()
{
	Jump();
	//Rope->DoSkill();
	/*Movement->SetMovementMode(EMovementMode::MOVE_Flying);
	PlayAnimMontage(testMontage);*/
}

void ACPlayer::OnDash()
{
	CheckFalse(DashSkill->GetSkillLevel() > 0);
	DashSkill->DoSkill();
}

void ACPlayer::OnPickUpWidget(UCItem* InItem)
{
	if (!!CheckItem)
		return;
	CheckItem = InItem;
	PickUpWidget->SetVisibility(ESlateVisibility::Visible);
	FVector2D position;
	GetController<APlayerController>()->ProjectWorldLocationToScreen(GetMesh()->GetSocketLocation("head"), position);
	position.X += 100;
	PickUpWidget->SetPositionInViewport(position, true);
}

void ACPlayer::OffPickUpWidget()
{
	PickUpWidget->SetVisibility(ESlateVisibility::Hidden);
	CheckItem = NULL;
}

void ACPlayer::OnRideWidget(ACHorse* InHorse)
{
	CheckNull(InHorse);
	CheckHorse = InHorse;
	RideWidget->SetVisibility(ESlateVisibility::Visible);
	FVector2D position;
	GetController<APlayerController>()->ProjectWorldLocationToScreen(GetMesh()->GetSocketLocation("head"), position);
	position.X += 100;
	RideWidget->SetPositionInViewport(position, true);
}

void ACPlayer::OffRideWidget()
{
	RideWidget->SetVisibility(ESlateVisibility::Hidden);
	CheckHorse = NULL;
}

//?????? ????
void ACPlayer::OnMoveForward(float AxisValue)
{
	CheckFalse(bCanMove);
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, AxisValue);
}

void ACPlayer::OnMoveRight(float AxisValue)
{
	CheckFalse(bCanMove);
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