#include "CEquipActor_Dual.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACEquipActor_Dual::ACEquipActor_Dual()
{

}

void ACEquipActor_Dual::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters params;
	params.Owner = OwnerCharacter;
	SubActor = GetWorld()->SpawnActor<ACEquipActor>(SubActorClass, params);

	TArray<class UShapeComponent*> collisions;
	SubActor->GetComponents<UShapeComponent>(collisions);
	
	for (UShapeComponent* collision : collisions)
	{
		collision->OnComponentBeginOverlap.AddDynamic(this, &ACEquipActor::OnComponentBeginOverlap);
	}

}

void ACEquipActor_Dual::AttachTo(FName InSocketName)
{
	Super::AttachTo(InSocketName);

	FString str = InSocketName.ToString() + "_Sub";
	InSocketName = FName(str);
	SubActor->AttachTo(InSocketName);
}

void ACEquipActor_Dual::SetVisibility(bool InBool)
{
	Super::SetVisibility(InBool);

	SubActor->SetVisibility(InBool);
}

void ACEquipActor_Dual::Equip()
{
	Super::Equip();
	SubActor->SetVisibility(true);
}

void ACEquipActor_Dual::Unequip()
{
	Super::Unequip();
	SubActor->SetVisibility(false);
}

void ACEquipActor_Dual::SetOwnerCharacter(ACharacter* InOwner)
{
	Super::SetOwnerCharacter(InOwner);

	SubActor->SetOwnerCharacter(InOwner);
}

void ACEquipActor_Dual::OnCollision()
{
	Super::OnCollision();
	CheckNull(SubActor);
	SubActor->OnCollision();
}

void ACEquipActor_Dual::OffCollision()
{
	Super::OffCollision();
	CheckNull(SubActor);
	SubActor->OffCollision();
}