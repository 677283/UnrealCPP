#include "CWindowWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Widget/CWidget_TitleBar.h"

void UCWindowWidget::NativeConstruct()
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

void UCWindowWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

FReply UCWindowWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UpdateZOrder();

	return reply;
}

//FReply UCWindowWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
//{
//	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
//
//	return reply;
//}

void UCWindowWidget::UpdateZOrder()
{
	OnZUpdate.ExecuteIfBound(this);
}

