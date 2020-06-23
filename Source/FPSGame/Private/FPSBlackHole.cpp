// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphere"));
	InnerSphere->SetupAttachment(MeshComp);

	OuterSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphere"));
	OuterSphere->SetupAttachment(MeshComp);

	OuterSphereSize = 2500.f;
	Strength = -2500.f;
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();

	InnerSphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::InnerOverlap);
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent *> Components;
	OuterSphere->GetOverlappingComponents(Components);

	for (UPrimitiveComponent *Comp : Components)
	{
		if (Comp && Comp->IsSimulatingPhysics())
		{
			Comp->AddRadialForce(GetActorLocation(), OuterSphereSize, Strength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}

void AFPSBlackHole::InnerOverlap(
	class UPrimitiveComponent *OverlappedComp,
	class AActor *OtherActor,
	class UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	OtherActor->Destroy();
}