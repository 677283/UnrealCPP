#include "CDisposeItem.h"
#include "Global.h"
#include "Item/CItemAsset.h"
#include "Item/CItem.h"
#include "CGameInstance.h"

ACDisposeItem::ACDisposeItem()
{

}

void ACDisposeItem::BeginPlay()
{
	Super::BeginPlay();
	/*CheckNull(ItemClass);
	UCItemAsset* Item = NewObject<UCItemAsset>(this, ItemClass);
	Item->BeginPlay(this);
	Item->DropItem(GetActorLocation());*/

	UCGameInstance* instance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UCItem* item = instance->CreateItem(this, CreateItemName);
	if (!item)
		CLog::Log("ItemNULL");
	else
		item->DropItem(GetActorLocation());

	Destroy();
}
