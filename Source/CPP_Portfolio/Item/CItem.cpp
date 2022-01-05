#include "CItem.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/CDropActor.h"
#include "Player/CPlayer.h"

UCItem::UCItem()
{
}

void UCItem::InitializeItem(FString InName, class ACDropActor* InDrop, EItemType InType, class UTexture2D* InIcon, int32 InMaxAmount)
{
	Name = InName;
	DropActor = InDrop;
	ItemType = InType;
	Icon = InIcon;
	MaxAmount = InMaxAmount;
}

void UCItem::UseItem()
{
	if (OnUpdateItem.IsBound())
		OnUpdateItem.Broadcast(this);

	if (Amount < 1)
		DestroyItem();
}

void UCItem::DestroyItem()
{
	DropActor->Destroy();
	
	if (OnDestroyItem.IsBound())
		OnDestroyItem.Broadcast(this);
	
	
	ConditionalBeginDestroy();

}

void UCItem::DropItem(FVector InDropPosition)
{
	OwnerCharacter = NULL;
	DropActor->Drop(InDropPosition);
}

void UCItem::PickUpItem(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
	DropActor->PickUp();
}

int32 UCItem::AddAmount(int32 InAmount)
{
	Amount += InAmount;

	return Amount > MaxAmount ? Amount -= MaxAmount : 0;
}

void UCItem::OnDropActorBeginOverlap(class ACPlayer* InPlayer)
{
	InPlayer->OnPickUpWidget(this);
}