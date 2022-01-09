#include "CGameInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/CItem.h"
#include "Item/CItemAsset.h"

UCGameInstance::UCGameInstance()
{
	
}

UCItem* UCGameInstance::CreateItem(ACharacter* InOwner, FString InItemName)
{
	UCItemAsset* asset = *(ItemList.Find(InItemName));
	
	if (!asset)
	{
		CLog::Log("DEV ERROR : AssetNULL");
		return NULL;
	}
	return asset->CreateItem(InOwner, NULL);
}