#include "CWidget_Damage.h"
#include "Global.h"

void UCWidget_Damage::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCWidget_Damage::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CLog::Log(WorldPosition);
	ZValue += InDeltaTime * ZPower;
	FVector pos = WorldPosition;
	//pos.Z += sin(ZValue) * Jump;
	FVector2D screenPos;
	
	int32 sizeX;
	int32 sizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(pos, screenPos);
	
	screenPos.Y -= sin(ZValue) * Jump;
	CLog::Log(screenPos.X);
	CLog::Log(screenPos.Y);
	if (screenPos.X<0 || screenPos.Y<0 || screenPos.X > sizeX || screenPos.Y > sizeY)
	{
		SetPositionInViewport(FVector2D(sizeX,sizeY));
		return;
	}
	
	SetPositionInViewport(screenPos);
}

void UCWidget_Damage::SetWorldPos(FVector InPosition)
{ 
	WorldPosition = InPosition;

	//FVector pos = WorldPosition;
	////pos.Z += sin(ZValue) * Jump;
	//FVector2D screenPos;

	//int32 sizeX;
	//int32 sizeY;
	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);

	//UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(pos, screenPos);

	////CLog::Log(screenPos.X);
	////CLog::Log(screenPos.Y);
	//if (screenPos.X<0 || screenPos.Y<0 || screenPos.X > sizeX || screenPos.Y > sizeY)
	//{
	//	SetPositionInViewport(FVector2D(sizeX, sizeY));
	//	return;
	//}

	//SetPositionInViewport(screenPos);
}