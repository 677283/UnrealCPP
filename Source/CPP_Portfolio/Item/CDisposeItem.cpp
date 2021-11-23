#include "CDisposeItem.h"
#include "Item/CItemAsset.h"

ACDisposeItem::ACDisposeItem()
{

}

void ACDisposeItem::BeginPlay()
{
	Super::BeginPlay();
	CheckNull(Item);
	Item->BeginPlay(this);
	Item->DropItem(GetActorLocation());
	Destroy();
}
