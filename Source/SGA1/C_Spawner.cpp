// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Spawner.h"
#include "C_Cube.h"
#include "C_Ramp.h"
#include "C_Cylinder.h"

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

	FString ClassPath3 = TEXT("Blueprint'/Game/Scene2/BP_C_Cylinder.BP_C_Cylinder_C'");
	CppMacro::GetClass(&CylinderClass, ClassPath3);
}

// Called when the game starts or when spawned
void AC_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Cube
	AC_Cube* SpawnActor1 = GetWorld()->SpawnActor<AC_Cube>(CubeClass);
	SpawnActor1->SetActorLocation(FVector(0, 0, 0));
	SpawnActor1->SetActorScale3D(FVector(0.5, 0.5, 2));

	// Ramp
	AC_Ramp* SpawnActor2 = GetWorld()->SpawnActor<AC_Ramp>(RampClass);
	SpawnActor2->SetActorLocation(FVector(-70, 20, 270));
	SpawnActor2->SetActorScale3D(FVector(2, 2, 2));
	SpawnActor2->SetActorRotation(FRotator(0, 0, 135));

	AC_Ramp* SpawnActor3 = GetWorld()->SpawnActor<AC_Ramp>(RampClass);
	SpawnActor3->SetActorLocation(FVector(-70, 20, 410));
	SpawnActor3->SetActorScale3D(FVector(2, 2, 2));
	SpawnActor3->SetActorRotation(FRotator(0, 0, 135));

	AC_Ramp* SpawnActor4 = GetWorld()->SpawnActor<AC_Ramp>(RampClass);
	SpawnActor4->SetActorLocation(FVector(-70, 20, 550));
	SpawnActor4->SetActorScale3D(FVector(2, 2, 2));
	SpawnActor4->SetActorRotation(FRotator(0, 0, 135));

	UKismetSystemLibrary::K2_SetTimer(this, "SpawnCylinder", 0.2f, true);


}

// Called every frame
void AC_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Spawner::SpawnCylinder()
{
	int x = UKismetMathLibrary::RandomIntegerInRange(-150, 150);
	int y = UKismetMathLibrary::RandomIntegerInRange(-150, 150);
	int z = UKismetMathLibrary::RandomIntegerInRange(100, 500);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FString::Printf(TEXT("%i, %i, %i"), x, y, z));

	AC_Cylinder* SpawnActor = GetWorld()->SpawnActor<AC_Cylinder>(CylinderClass);
	SpawnActor->SetActorLocation(FVector(x, y, z));
	SpawnActor->SetActorScale3D(FVector(0.1, 0.1, 0.1));
}

