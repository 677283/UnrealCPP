#include "CWidget_DragAndDrop.h"
#include "Global.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
//#include "Blueprint/WidgetTree.h"

void UCWidget_DragAndDrop::NativeConstruct()
{
	Super::NativeConstruct();
	Icon = Cast<UImage>(GetWidgetFromName(*IconSlotName));
	bIsActive = false;
}

void UCWidget_DragAndDrop::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	CheckFalse(bIsActive);

	float x, y;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
	FVector2D pos(x, y);
	FVector2D size = Icon->GetCachedGeometry().GetDrawSize();

	pos.X -= size.X / 2.0f;
	pos.Y -= size.Y / 2.0f;

	//pos = pos / UWidgetLayoutLibrary::GetViewportScale(GetWorld());

	SetPositionInViewport(pos);

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0)->WasInputKeyJustReleased(FKey("LeftMouseButton")))
		SetActive(false);
}

void UCWidget_DragAndDrop::SetIcon(class UTexture2D* InIcon)
{
	Icon->SetBrushFromTexture(InIcon);
}

void UCWidget_DragAndDrop::SetActive(bool InActive)
{
	bIsActive = InActive;

	if (bIsActive)
	{
		float x, y;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(x, y);
		FVector2D pos(x, y);
		FVector2D size = Icon->GetCachedGeometry().GetDrawSize();

		pos.X -= size.X / 2.0f;
		pos.Y -= size.Y / 2.0f;

		//pos = pos / UWidgetLayoutLibrary::GetViewportScale(GetWorld());

		SetPositionInViewport(pos);
		SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}