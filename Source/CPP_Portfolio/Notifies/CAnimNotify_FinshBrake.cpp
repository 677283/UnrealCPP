#include "CAnimNotify_FinshBrake.h"
#include "Global.h"
#include "Horse/CHorse.h"

FString UCAnimNotify_FinshBrake::GetNotifyName_Implementation() const
{
	return "Finish_Brake";
}

void UCAnimNotify_FinshBrake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());
	
	ACHorse* horse = Cast<ACHorse>(MeshComp->GetOwner());

	CheckNull(horse);
	horse->FinishBrake();
}
