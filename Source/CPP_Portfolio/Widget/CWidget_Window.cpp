#include "CWidget_Window.h"
#include "Blueprint/WidgetTree.h"
#include "Widget/CWidget_TitleBar.h"

void UCWidget_Window::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UWidget*> widgets;
	WidgetTree->GetAllWidgets(widgets);

	for (UWidget* widget : widgets)
	{
		UCWidget_TitleBar* titleBar = Cast<UCWidget_TitleBar>(widget);

		if (!titleBar) continue;

		titleBar->SetMove(this);
		break;
	}
	
}

void UCWidget_Window::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

FReply UCWidget_Window::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UpdateZOrder();

	return reply;
}

//FReply UCWidget_Window::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
//
//	return reply;
//}

void UCWidget_Window::UpdateZOrder()
{
	OnZUpdate.ExecuteIfBound(this);
}

