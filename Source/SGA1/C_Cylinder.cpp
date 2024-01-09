// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Cylinder.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "CppMacro.h"

// Sets default values
AC_Cylinder::AC_Cylinder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, MeshComponent, TEXT("Mesh"), Root);

	FString MeshPath = TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder'");
	CppMacro::GetObject(CylinderMesh, MeshPath);
	MeshComponent->SetStaticMesh(CylinderMesh);

	FString MaterialPath = TEXT("Material'/Game/Characters/Mannequins/Materials/Instances/Manny/M_Mannequin_red_Inst.M_Mannequin_red_Inst'");
	ConstantMaterial = Cast<UMaterialInstanceConstant>(
		StaticLoadObject(UMaterialInstanceConstant::StaticClass(), NULL, *MaterialPath));
}

// Called when the game starts or when spawned
void AC_Cylinder::BeginPlay()
{
	Super::BeginPlay();

	DynamicMaterial = UMaterialInstanceDynamic::Create(ConstantMaterial, this);
	MeshComponent->SetMaterial(0, DynamicMaterial);

	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::Red);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 0.1f, true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DestroySelf, this, &AC_Cylinder::DestroySelf, 4.0f, false);
}

// Called every frame
void AC_Cylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Cylinder::ChangeColor()
{
	DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FLinearColor::MakeRandomColor());
}

void AC_Cylinder::DestroySelf()
{
	if (IsValid(this))
	{
		Destroy();
	}
}

