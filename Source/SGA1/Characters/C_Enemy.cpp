// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_Enemy.h"

#include "Weapons/C_Sword.h"

#include "Engine/SkeletalMesh.h"
#include "CppMacro.h"

// Sets default values
AC_Enemy::AC_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Skeletal Mesh
	FString MeshPath = TEXT("SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'");
	CppMacro::GetObject<USkeletalMesh>(SkeletalMesh, MeshPath);
	GetMesh()->SetSkeletalMesh(SkeletalMesh);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0)); // Pitch, Yaw, Roll

}

// Called when the game starts or when spawned
void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	Sword = AC_Sword::Spawn(this);
	Sword->Equip();
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

