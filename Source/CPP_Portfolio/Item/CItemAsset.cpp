#include "CItemAsset.h"
#include "Global.h"
#include "GameFramework/Character.h"


UCItemAsset::UCItemAsset()
{
	ItemType = EItemType::None;
}

void UCItemAsset::BeginPlay(class ACharacter* InOwner)
{
	OwnerCharacter = InOwner;
}
