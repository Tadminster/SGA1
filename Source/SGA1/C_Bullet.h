// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Bullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SGA1_API AC_Bullet : public AActor
{
	GENERATED_BODY()
	
private:
	// Mesh
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	// Movement
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UProjectileMovementComponent* Movement;

	// Collision
	//UPROPERTY(VisibleAnywhere, Category = "Collision")
	//USphereComponent* Collision;

private:
	FVector Direction;
	float	Speed;
	float	CurrentTime;
	float	LifeTime;
	float	Damage;

public:	
	// Sets default values for this actor's properties
	AC_Bullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(FVector _Location, FVector _Direction);
};
