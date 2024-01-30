// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_Prototype.h"

// Sets default values
AC_Prototype::AC_Prototype()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Prototype::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Prototype::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

