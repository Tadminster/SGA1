// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Cube.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "CppMacro.h"

// Sets default values
AC_Cube::AC_Cube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, MeshComponent, TEXT("Mesh"), Root);

	FString MeshPath = TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube'");
	CppMacro::GetObject(CubeMesh, MeshPath);
	MeshComponent->SetStaticMesh(CubeMesh);

	FString MaterialPath = TEXT("Material'/Game/Characters/Mannequins/Materials/Instances/Manny/M_Mannequin_red_Inst.M_Mannequin_red_Inst'");
	ConstantMaterial = Cast<UMaterialInstanceConstant>(
	StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, *MaterialPath));
}

// Called when the game starts or when spawned
void AC_Cube::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = UMaterialInstanceDynamic::Create(ConstantMaterial, this);
	MeshComponent->SetMaterial(0, DynamicMaterial);

	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Red);


}

// Called every frame
void AC_Cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

