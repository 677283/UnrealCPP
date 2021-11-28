#include "CDisposeItem.h"
#include "Item/CItemAsset.h"

ACDisposeItem::ACDisposeItem()
{

}

void ACDisposeItem::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(ItemClass);
	UCItemAsset* Item = NewObject<UCItemAsset>(this, ItemClass);
	Item->BeginPlay(this);
	Item->DropItem(GetActorLocation());
	Destroy();
}
