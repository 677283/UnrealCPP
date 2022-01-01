#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWidget_HUD.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	class UWidget* GetWidget(FString InWidgetName);
	void ToggleWidget(FString InWidgetName);
	int32 FindIndex(FString InName);
	void SetZOrder(class UWidget* InWidget);

public:
	FORCEINLINE class UPanelWidget* GetMainPanel() { return MainPanel; }

private:
	class UPanelWidget* MainPanel;
	TArray<class UWidget*> Widgets;
	int32 ZOrder=1;
};
