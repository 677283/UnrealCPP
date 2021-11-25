#include "CItemAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Item/CDropActor.h"
#include "Player/CPlayer.h"


UCItemAsset::UCItemAsset()
{
	ItemType = EItemType::None;
	DropActorClass = ACDropActor::StaticClass();
}

void UCItemAsset::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	DropActor = InOwner->GetWorld()->SpawnActor<ACDropActor>(DropActorClass, params);
	DropActor->OnDropActorBeginOverlap.AddDynamic(this, &UCItemAsset::OnDropActorBeginOverlap);
}

void UCItemAsset::DropItem(FVector InDropPosition)
{
	DropActor->Drop(InDropPosition);
	OwnerCharacter = NULL;
}

void UCItemAsset::PickUpItem(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}

void UCItemAsset::OnDropActorBeginOverlap(class ACPlayer* InPlayer)
{
	InPlayer->OnPickUpWidget(this);
}	