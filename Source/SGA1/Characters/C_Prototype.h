// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Prototype.generated.h"

class USkeletalMesh;
class AC_Sword;

UCLASS(Abstract)
class SGA1_API AC_Prototype : public ACharacter
{
	GENERATED_BODY()

protected:
	// SkeletalMesh
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh{ nullptr };

	// Weapon
	UPROPERTY(EditDefaultsOnly)
	AC_Sword* Sword;



public:
	// Sets default values for this character's properties
	AC_Prototype();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual AC_Sword* GetSword() { return Sword; };
};
