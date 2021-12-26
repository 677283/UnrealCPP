#include "CEquipComponent.h"
#include "Global.h"
#include "Item/Equip/Weapon/CWeaponItem.h"
#include "Item/Equip/Weapon/CEquipment_Weapon.h"
#include "Widget/CWidget_Equip.h"
#include "GameFramework/Character.h"
#include "Widget/CWidget_HUD.h"
#include "Player/CPlayer.h"
#include "Components/PanelWidget.h"

#include "Components/CanvasPanelSlot.h"
UCEquipComponent::UCEquipComponent()
{
	CHelpers::GetClass(&EquipWidgetClass, "WidgetBlueprint'/Game/__ProjectFile/Widgets/Equip/WB_Equip.WB_Equip_C'");
}

void UCEquipComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
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

void UCEquipComponent::AddWidget()
{

	EquipWidget = CreateWidget<UCWidget_Equip, APlayerController>(OwnerCharacter->GetController<APlayerController>(), EquipWidgetClass, "Equip");
	EquipWidget->SetVisibility(ESlateVisibility::Hidden);
	EquipWidget->OnEquipAction.BindUObject(this, &UCEquipComponent::UnequipItem);

	if (!!Cast<ACPlayer>(GetOwner())->GetHUD())
		Cast<ACPlayer>(GetOwner())->GetHUD()->GetMainPanel()->AddChild(EquipWidget);

	//Cast<UCanvasPanelSlot>(EquipWidget->Slot)->SetZOrder(1);
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
		EquipWidget->SetSlotIcon("Weapon", icon);
		break;
	case EEquipType::Armor:
		//TODO °©¿Ê ÀåÂø
		break;
	}
}

void UCEquipComponent::UnequipItem(FString InName)
{
	if (InName == "Weapon")
	{
		if(OnUnequip.IsBound())
			OnUnequip.Broadcast(nullptr, Weapon);
		Weapon = nullptr;
	}

}

bool UCEquipComponent::IsHandsOn()
{
	return *(Weapon->GetEquipment()->GetHands());
}