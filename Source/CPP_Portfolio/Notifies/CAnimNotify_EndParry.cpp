#include "CAnimNotify_EndParry.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/CParryingComponent.h"

FString UCAnimNotify_EndParry::GetNotifyName_Implementation() const
{
	return "EndDoParry";
}

void UCAnimNotify_EndParry::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCParryingComponent* parrying = CHelpers::GetComponent<UCParryingComponent>(MeshComp->GetOwner());

	CheckNull(parrying);

	parrying->EndDoParry();
}
