// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Sword.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "CppMacro.h"

// Sets default values
AC_Sword::AC_Sword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateComponet(this, Root, TEXT("Root"));
	CppMacro::CreateComponet(this, SkeletalMesh, TEXT("Mesh"), Root);
}

// Called when the game starts or when spawned
void AC_Sword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

