#include "CRope.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

ACRope::ACRope()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle", GetRootComponent());

}

void ACRope::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACRope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Power += DeltaTime * 5000;
	Particle->SetBeamTargetPoint(0, GetActorLocation() + Target * Power, 0);
	if (Power > 1000)
	{
		SetActorTickEnabled(false);
	}
}

void ACRope::SetTargetPosition(FVector position)
{
	Target = position;
	SetActorTickEnabled(true);
	Particle->SetBeamTargetPoint(0, GetActorLocation() + Target, 0);
	OnParticle();
}

void ACRope::OnParticle()
{
	Power = 0;
	Particle->SetBeamTargetPoint(0, GetActorLocation() + Target * Power, 0);
	Particle->SetVisibility(true);
}

void ACRope::OffParticle()
{
	Particle->SetVisibility(false);
}
