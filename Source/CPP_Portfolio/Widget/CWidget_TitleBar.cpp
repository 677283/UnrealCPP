#include "CWidget_TitleBar.h"
#include "Global.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/CWidget_TitleBar_Button.h"

void UCWidget_TitleBar::NativeConstruct()
{
//	MoveSlot = Cast<UCanvasPanelSlot>(MoveWidget->Slot);
	Super::NativeConstruct();
	Flag = false;

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_TitleBar_Button* button = Cast<UCWidget_TitleBar_Button>(widget);
		if (!!button)
			button->OnMouseDwon.BindUObject(this, &UCWidget_TitleBar::OnTitleBarButtonDown);
	}

}

void UCWidget_TitleBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CheckFalse(Flag);

	float x, y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
	FVector2D pos(x, y);

	pos = pos / UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	MoveSlot->SetPosition(pos - Offset);

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustReleased(FKey("LeftMouseButton")))
		Flag = false;
}

FReply UCWidget_TitleBar::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (MoveWidget->IsVisible())
		Flag = true;

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);

	float x, y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
	FVector2D pos(x, y);
	pos = pos / UWidgetLayoutLibrary::GetViewportScale(GetWorld());
	Offset = pos - MoveSlot->GetPosition();

	return reply;
}

FReply UCWidget_TitleBar::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	Flag = false;

	UGameViewportClient* Viewport = GEngine->GameViewport;
	Viewport->SetMouseCaptureMode(EMouseCaptureMode::CaptureDuringMouseDown);

	return reply;
}

//void UCWidget_TitleBar::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
//{
//	Super::NativeOnMouseLeave(InMouseEvent);
//
//	CheckFalse(Flag);
//
//	float x, y;
//	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
//	FVector2D pos(x, y);
//
//	pos = pos / UWidgetLayoutLibrary::GetViewportScale(GetWorld());
//
//	MoveSlot->SetPosition(pos - Offset);
//}

void UCWidget_TitleBar::SetMove(class UUserWidget* InWidget)
{
	MoveWidget = InWidget;
	MoveSlot = Cast<UCanvasPanelSlot>(InWidget->Slot);
}

void UCWidget_TitleBar::OnTitleBarButtonDown()
{
	Flag = false;

	MoveWidget->SetVisibility(ESlateVisibility::Hidden);
}