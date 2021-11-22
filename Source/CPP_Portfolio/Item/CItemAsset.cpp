#include "CItemAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/CDropActor.h"


UCItemAsset::UCItemAsset()
{
	ItemType = EItemType::None;
}

void UCItemAsset::BeginPlay(class AActor* InOwner)
{
	OwnerCharacter = InOwner;
}

void UCItemAsset::DropItem()
{
	DropActor->Drop();
}

void UCItemAsset::PickUpItem()
{
	DropActor->PickUp();
}