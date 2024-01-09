// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Sword.generated.h"

class USkeletalMeshComponent;
class USceneComponent;

UCLASS()
class SGA1_API AC_Sword : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent*	SkeletalMesh;

public:	
	// Sets default values for this actor's properties
	AC_Sword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
