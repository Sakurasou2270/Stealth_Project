// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "FPSCharacter.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetBoxExtent(FVector(100.f));
	BoxComp->SetupAttachment(MeshComp);

	LaunchStrength = 1100.f;
	LaunchAngle = 37.f;
}

void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OnComponentOverlap);
}

void AFPSLaunchPad::OnComponentOverlap(
	UPrimitiveComponent *OverlappedComponent,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LaunchPadFX, FTransform(FRotator(0.f), GetActorLocation()));

	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	AFPSCharacter *Player = Cast<AFPSCharacter>(OtherActor);
	if (Player)
	{
		Player->LaunchCharacter(LaunchVelocity, true, true);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
	}
}