// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *SphereComp;
};
