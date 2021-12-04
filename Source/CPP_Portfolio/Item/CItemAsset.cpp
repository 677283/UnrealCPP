#include "CItemAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/CDropActor.h"
#include "Player/CPlayer.h"
#include "Item/CItem.h"

UCItemAsset::UCItemAsset()
{
	ItemType = EItemType::None;
	DropActorClass = ACDropActor::StaticClass();
}

UCItem* UCItemAsset::CreateItem(ACharacter* InOwner, UCItem* InItem)
{
	if (!InItem)
	{
		InItem = NewObject<UCItem>();
	}

	FActorSpawnParameters params;
	params.Owner = InOwner;
	ACDropActor* dropActor = InOwner->GetWorld()->SpawnActor<ACDropActor>(DropActorClass, params);
	dropActor->OnDropActorBeginOverlap.AddDynamic(InItem, &UCItem::OnDropActorBeginOverlap);

	InItem->InitializeItem(Name, dropActor, ItemType, Icon, MaxAmount);

	ItemList.Add(InItem);
	return InItem;
}