// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Cylinder.generated.h"

UCLASS()
class SGA1_API AC_Cylinder : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle TimerHandle_DestroySelf;

protected:
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent*		Root;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMesh*			CylinderMesh;

	class UMaterialInstanceConstant*	ConstantMaterial;
	class UMaterialInstanceDynamic*		DynamicMaterial;
	
public:	
	// Sets default values for this actor's properties
	AC_Cylinder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ChangeColor();

	UFUNCTION()
	void DestroySelf();
};
