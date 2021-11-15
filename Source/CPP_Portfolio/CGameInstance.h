#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "CGameInstance.generated.h"

UCLASS()
class CPP_PORTFOLIO_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCGameInstance();

private:
	class UDataTable* DataTable;
};
