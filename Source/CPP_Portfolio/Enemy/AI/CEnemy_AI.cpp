#include "CEnemy_AI.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", GetRootComponent());

	Text->SetRelativeLocation(FVector(0, 0, 100));
}

void ACEnemy_AI::SetDetected(bool InDetected)
{
	if (InDetected)
		Text->SetText("!");
	else
		Text->SetText("?");
}

void ACEnemy_AI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector dir = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation() - GetActorLocation();

	dir.Normalize();

	float scalar = UKismetMathLibrary::Dot_VectorVector(dir, GetActorForwardVector());

	float degree = UKismetMathLibrary::DegAcos(scalar);

	UKismetMathLibrary::DegAcos(scalar);

	Text->SetRelativeRotation(FRotator(0, degree, 0));
}