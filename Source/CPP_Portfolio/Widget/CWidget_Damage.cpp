#include "CWidget_Damage.h"
#include "Global.h"
#include "Components/TextBlock.h"

void UCWidget_Damage::NativeConstruct()
{
	Super::NativeConstruct();

	Text = Cast<UTextBlock>(GetWidgetFromName("DamageText"));

	if (!!Text)
		Text->SetText(FText::FromString(Damage));
}

void UCWidget_Damage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	StackSpawnLife += InDeltaTime;
	YOffset += InDeltaTime * YOffsetSpeed;
	XOffset += XOffsetSpeed * InDeltaTime;

	FVector pos = WorldPosition;
	FVector2D screenPos;
	
	int32 sizeX, sizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(pos, screenPos);
	
	screenPos.Y -= sin(YOffset) * YHeight;
	screenPos.X += XOffset;

	if (screenPos.X<0 || screenPos.Y<0 || screenPos.X > sizeX || screenPos.Y > sizeY)
	{
		SetPositionInViewport(FVector2D(sizeX,sizeY));
		return;
	}

	SetPositionInViewport(screenPos);
	if (StackSpawnLife > SpawnLife)
		RemoveFromParent();
}

void UCWidget_Damage::SetWorldPos(FVector InPosition, FString InDamage)
{ 
	WorldPosition = InPosition;
	Damage = InDamage;
}