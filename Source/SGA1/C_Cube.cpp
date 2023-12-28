// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Cube.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_Cube::AC_Cube() : 
	Root(CreateDefaultSubobject<USceneComponent>(TEXT("Root"))),
	Child(CreateDefaultSubobject<USceneComponent>(TEXT("Child"))),
	MeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SetRootComponent(Root);
	Child->SetupAttachment(Root);
	MeshComponent->SetupAttachment(Child);
	
	FString MeshPath = TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'");
	// 경로를 통해 에셋 찾기
	static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(*MeshPath);
	
	// 멤버 변수에 에셋을 할당
	CubeMesh = asset.Object;
	if (asset.Succeeded()) // 에셋이 존재하면
	{
		// 메쉬 컴포넌트에 에셋을 할당
		MeshComponent->SetStaticMesh(CubeMesh);
	}

	//if (asset.Succeeded())
	//{
		//MeshComponent->SetStaticMesh(asset.Object);
	//}

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

