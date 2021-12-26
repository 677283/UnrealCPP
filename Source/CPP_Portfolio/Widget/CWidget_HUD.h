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
	FORCEINLINE class UPanelWidget* GetMainPanel() { return MainPanel; }

private:
	class UPanelWidget* MainPanel;
};
