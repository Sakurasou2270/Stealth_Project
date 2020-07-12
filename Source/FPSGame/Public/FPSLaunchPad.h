// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()

public:
	AFPSLaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent *BoxComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystem *LaunchPadFX;

	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float LaunchStrength;

	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float LaunchAngle;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentOverlap(
		UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);
};
