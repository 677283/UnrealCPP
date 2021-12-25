#include "CEquipComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Widget/CWidget_Equip.h"
#include "GameFramework/Character.h"

UCEquipComponent::UCEquipComponent()
{
	CHelpers::GetClass(&EquipWidgetClass, "WidgetBlueprint'/Game/__ProjectFile/Widgets/Equip/WB_Equip.WB_Equip_C'");
}

void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	EquipWidget = CreateWidget<UCWidget_Equip, APlayerController>(OwnerCharacter->GetController<APlayerController>(), EquipWidgetClass, "Equip");
	EquipWidget->AddToViewport();
	EquipWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UCEquipComponent::WidgetToggle()
{
	if (EquipWidget->IsVisible())
	{
		OwnerCharacter->GetController<APlayerController>()->SetShowMouseCursor(false);
		OwnerCharacter->GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());
		EquipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		OwnerCharacter->GetController<APlayerController>()->SetShowMouseCursor(true);

		FInputModeGameAndUI mode;
		mode.SetHideCursorDuringCapture(false);
		mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		OwnerCharacter->GetController<APlayerController>()->SetInputMode(mode);

		EquipWidget->SetVisibility(ESlateVisibility::Visible);
		EquipWidget->SetFocus();
	}
}

void UCEquipComponent::EquipItem(UCEquipItem* InItem)
{
	CheckNull(InItem);

	switch (InItem->GetEquipType())
	{
	case EEquipType::Weapon:
		if (OnEquip.IsBound())
			OnEquip.Broadcast(InItem, Weapon);

		Weapon = Cast<UCWeaponItem>(InItem);
		
		UTexture2D* icon;
		!!Weapon ? icon = Weapon->GetIcon() : icon = nullptr;
		EquipWidget->SetSlotIcon(EEquipSlot::Weapon, icon);
		break;
	case EEquipType::Armor:
		//TODO °©¿Ê ÀåÂø
		break;
	}
}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}