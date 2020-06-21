// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USphereComponent *InnerSphere;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USphereComponent *OuterSphere;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float OuterSphereSize;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float Strength;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void InnerOverlap(
		class UPrimitiveComponent *OverlappedComp,
		class AActor *OtherActor,
		class UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);
};
