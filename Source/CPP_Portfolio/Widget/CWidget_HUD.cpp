#include "CWidget_HUD.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanelSlot.h"

#define INVENTORY 0
#define EQUIP 1
#define SKILLTREE 2

void UCWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	MainPanel = Cast<UPanelWidget>(GetWidgetFromName("MainPanel"));

	Widgets.Add(GetWidgetFromName("Inventory"));
	Widgets.Add(GetWidgetFromName("Equip"));
	Widgets.Add(GetWidgetFromName("SkillTree"));

	//Cast<UCanvasPanelSlot>(Widgets[0]->Slot)->SetZOrder()
}

UWidget* UCWidget_HUD::GetWidget(FString InWidgetName)
{
	int32 index = FindIndex(InWidgetName);
	if (index == -1) return nullptr;

	return Widgets[index];
}

void UCWidget_HUD::ToggleWidget(FString InWidgetName)
{
	int32 index = FindIndex(InWidgetName);

	bool setting = true;
	if (!Widgets[index]->IsVisible())
	{
		for (UWidget* widget : Widgets)
		{
			if (widget->IsVisible())
			{
				setting = false;
				break;
			}
		}
		Widgets[index]->SetVisibility(ESlateVisibility::Visible);
		SetZOrder(Widgets[index]);
		if (setting)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(true);
			FInputModeGameAndUI mode;
			mode.SetHideCursorDuringCapture(false);
			mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(mode);
		}
	}
	else
	{
		Widgets[index]->SetVisibility(ESlateVisibility::Hidden);
		for (UWidget* widget : Widgets)
		{
			if (widget->IsVisible())
			{
				setting = false;
				break;
			}
		}
		if (setting)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
			ZOrder = 0;
		}
	}

	
}

int32 UCWidget_HUD::FindIndex(FString InName)
{
	if (InName == "Inventory")
		return INVENTORY;
	else if (InName == "Equip")
		return EQUIP;
	else if (InName == "SkillTree")
		return SKILLTREE;

	return -1;
}

void UCWidget_HUD::SetZOrder(class UWidget* InWidget)
{
	Cast<UCanvasPanelSlot>(InWidget->Slot)->SetZOrder(ZOrder);
	ZOrder++;
}
