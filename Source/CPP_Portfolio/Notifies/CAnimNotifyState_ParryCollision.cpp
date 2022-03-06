#include "CAnimNotifyState_ParryCollision.h"
#include "Global.h"
#include "Components/CParryingComponent.h"

FString UCAnimNotifyState_ParryCollision::GetNotifyName_Implementation() const
{
	return "ParryingCollision";
}

void UCAnimNotifyState_ParryCollision::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCParryingComponent* parrying = CHelpers::GetComponent<UCParryingComponent>(MeshComp->GetOwner());
	CheckNull(parrying);

	parrying->OnCollision();
}

void UCAnimNotifyState_ParryCollision::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	UCParryingComponent* parrying = CHelpers::GetComponent<UCParryingComponent>(MeshComp->GetOwner());
	CheckNull(parrying);

	parrying->OffCollision();
}
