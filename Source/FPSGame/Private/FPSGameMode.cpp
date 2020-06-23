// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn *InstigatorPawn)
{
	if (InstigatorPawn)
	{
		//! If a valid pawn exists then disable input
		InstigatorPawn->DisableInput(nullptr);
		if (SpectatorViewPoint)
		{
			//! Getting player controller and checking if any viewpoint classes are in level
			APlayerController *PC = Cast<APlayerController>(InstigatorPawn->GetController());
			TArray<AActor *> Spectator;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatorViewPoint, Spectator);

			//! Change viewtarget if any classes are found
			if (Spectator.Num() > 0)
			{
				AActor *NewViewTarget;
				NewViewTarget = Spectator[0];

				//! If player controller exists then set new view target
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 3.f, VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No Spectating ViewPointClass Found In GameMode Class"));
		}
	}

	OnMissionCompleted(InstigatorPawn);
}