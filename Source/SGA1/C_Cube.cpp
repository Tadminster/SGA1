// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Cube.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_Cube::AC_Cube() : 
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Cube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

