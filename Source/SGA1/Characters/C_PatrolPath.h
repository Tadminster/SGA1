// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_PatrolPath.generated.h"

class USceneComponent;
class USplineComponent;
class UTextRenderComponent;

UCLASS()
class SGA1_API AC_PatrolPath : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere) // Root
	USceneComponent* SceneComponent; 

	UPROPERTY(VisibleAnywhere) // Spline
	USplineComponent* SplineComponent; 

	UPROPERTY(VisibleAnywhere) // TextRender
	UTextRenderComponent* TextRenderComponent;// TextRender
	
	UPROPERTY(EditAnywhere, Category = "Loop")
	bool bClosedLoop;

	// How close the AI needs to be to the next patrol point to move to the next one
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius{ 100.0f };

	//UPROPERTY(VisibleAnywhere)
	//TArray<FVector> PatrolPoints;

public:	
	// Sets default values for this actor's properties
	AC_PatrolPath();

	//
	virtual void OnConstruction(const FTransform& Transform) override;

	FORCEINLINE USplineComponent* GetSplineComponent() const { return SplineComponent; }
	FORCEINLINE float GetAcceptanceRadius() const { return AcceptanceRadius; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
