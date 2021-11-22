#include "CDisposeItem.h"
#include "Global.h"
#include "Item/CItemAsset.h"

ACDisposeItem::ACDisposeItem()
{

}

void ACDisposeItem::BeginPlay()
{
	Super::BeginPlay();
	
	Item->BeginPlay(NULL);

}
