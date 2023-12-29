// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Cube.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "CppMacro.h"

// Sets default values
AC_Cube::AC_Cube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, Child, TEXT("Child"), Root);
	CppMacro::CreateComponet(this, MeshComponent, TEXT("Mesh"), Child);

	FString MeshPath = TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'");
	CppMacro::GetAsset(CubeMesh, MeshPath);
	MeshComponent->SetStaticMesh(CubeMesh);
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

