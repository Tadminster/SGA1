// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_Enemy.h"

// Sets default values
AC_Enemy::AC_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Enemy::ChangeMeshColor_Implementation(const FLinearColor& Color)
{
}

void AC_Enemy::Attack()
{
}

