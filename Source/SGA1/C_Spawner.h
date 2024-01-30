// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Spawner.generated.h"

UCLASS()
class SGA1_API AC_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Spawner();

	//TSubclassOf<class AC_Cube> CubeClass;
	//TSubclassOf<class AC_Ramp> RampClass;
	//TSubclassOf<class AC_Cylinder> CylinderClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnCylinder();

};
