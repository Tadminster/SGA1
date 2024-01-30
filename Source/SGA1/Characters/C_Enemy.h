// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/I_Character.h"
#include "C_Enemy.generated.h"

UCLASS()
class SGA1_API AC_Enemy : public ACharacter, public II_Character
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ChangeMeshColor_Implementation(const FLinearColor& Color) override;
	virtual void Attack() override;

};
