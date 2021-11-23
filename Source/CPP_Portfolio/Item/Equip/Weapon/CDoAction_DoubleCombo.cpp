#include "CDoAction_DoubleCombo.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/InputSettings.h"

void UCDoAction_DoubleCombo::DoAction(FKey InKey)
{
	Super::DoAction(InKey);
	CheckFalse(*bHands);

	if (bComboEnable)
	{
		LastKey = InKey;
		bOnCombo = true;
		return;
	}

	CheckFalse(State->IsStateIdle());

	if (InKey == EKeys::LeftMouseButton)
		ComboKey.Append("L");
	else
		ComboKey.Append("R");

	FDoActionData* actionData = ComboList.Find(ComboKey);

	if (!actionData)
	{
		ComboKey = "";
		return;
	}

	OwnerCharacter->PlayAnimMontage(ComboList.Find(ComboKey)->Montage);
	State->SetStateAction();
}

void UCDoAction_DoubleCombo::BeginDoAction()
{
	Super::BeginDoAction();
	
	CheckFalse(bOnCombo);

	bOnCombo = false;

	if (LastKey == EKeys::LeftMouseButton)
		ComboKey.Append("L");
	else
		ComboKey.Append("R");

	FDoActionData* data = ComboList.Find(ComboKey);
	
	CheckNull(data);

	OwnerCharacter->StopAnimMontage();
	OwnerCharacter->PlayAnimMontage(data->Montage);
}

void UCDoAction_DoubleCombo::EndDoAction()
{
	Super::EndDoAction();

	ComboKey = "";
	bOnCombo = false;

	State->SetStateIdle();
}

void UCDoAction_DoubleCombo::OnEquipActorBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	//InOtherCharacter->TakeDamage()

	for (ACharacter* character : HittedCharacters)
	{
		if (character == InOtherCharacter)
			return;
	}

	HittedCharacters.AddUnique(InOtherCharacter);

	if (OnDoActionBeginOverlap.IsBound())
		OnDoActionBeginOverlap.Broadcast(InAttacker, InAttackCauser, InOtherCharacter, ComboList.Find(ComboKey)->AddDamage);
}