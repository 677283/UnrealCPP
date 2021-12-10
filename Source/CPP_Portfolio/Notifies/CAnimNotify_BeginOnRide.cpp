#include "CAnimNotify_BeginOnRide.h"
#include "Global.h"
#include "Components/CRidingComponent.h"

FString UCAnimNotify_BeginOnRide::GetNotifyName_Implementation() const
{
	return "Begin_OnRide";
}

void UCAnimNotify_BeginOnRide::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCRidingComponent* riding = CHelpers::GetComponent<UCRidingComponent>(MeshComp->GetOwner());

	CheckNull(riding);

	riding->BeginOnRide();
}

