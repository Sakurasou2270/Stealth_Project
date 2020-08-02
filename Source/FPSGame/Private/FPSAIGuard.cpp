// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "FPSGameMode.h"
#include "TimerManager.h"

#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	PrimaryActorTick.bCanEverTick = false;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	GuardState = EAIState::Idle;
	OriginalRotation = GetActorRotation();
}

void AFPSAIGuard::OnPawnSeen(APawn *SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 10, FColor::Green, false, 7.0f, 0, 5.0f);

	AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		// The player is going to trigger this event
		GM->CompleteMission(SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float Volume)
{
	// if (GuardState == EAIState::Alerted)
	// {
	// 	return;
	// }

	DrawDebugSphere(GetWorld(), Location, 32.0f, 10, FColor::Yellow, false, 7.0f, 0, 5.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAt.Pitch = 0.0f;
	LookAt.Roll = 0.0f;

	SetActorRotation(LookAt);

	// Resetting the timer when distracted again
	GetWorldTimerManager().ClearTimer(TimerHandleResetRotation);
	GetWorldTimerManager().SetTimer(TimerHandleResetRotation, this, &AFPSAIGuard::ResetRotation, 3.0f);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::ResetRotation()
{
	// if (GuardState == EAIState::Alerted)
	// {
	// 	return;
	// }

	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;
	OnStateChanged(NewState);
}