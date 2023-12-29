// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Spawner.h"
#include "C_Cube.h"
#include "C_Ramp.h"

#include "CppMacro.h"

// Sets default values
AC_Spawner::AC_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString ClassPath1 = TEXT("Blueprint'/Game/Scene2/BP_C_Cube.BP_C_Cube_C'");
	CppMacro::GetClass(&CubeClass, ClassPath1);

	FString ClassPath2 = TEXT("Blueprint'/Game/Scene2/BP_C_Ramp.BP_C_Ramp_C'");
	CppMacro::GetClass(&RampClass, ClassPath2);
}

// Called when the game starts or when spawned
void AC_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	AC_Cube* SpawnActor1 = GetWorld()->SpawnActor<AC_Cube>(CubeClass);
	SpawnActor1->SetActorLocation(FVector(0, 0, 0));

	//AC_Cube* SpawnActor2 = GetWorld()->SpawnActor<AC_Cube>(CubeClass);
	//SpawnActor2->SetActorLocation(FVector(0, 0, 100));

	AC_Ramp* SpawnActor2 = GetWorld()->SpawnActor<AC_Ramp>(RampClass);
	SpawnActor2->SetActorLocation(FVector(0, 0, 100));
}

// Called every frame
void AC_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

