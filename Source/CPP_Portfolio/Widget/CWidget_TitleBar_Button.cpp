#include "CWidget_TitleBar_Button.h"


void UCWidget_TitleBar_Button::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply UCWidget_TitleBar_Button::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	OnMouseDwon.ExecuteIfBound();

	return reply;
}