// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Character.generated.h"

class USkeletalMesh;
class AC_Sword;
struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UI_Character : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SGA1_API II_Character
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ChangeMeshColor(const FLinearColor& Color);

	virtual void Attack() = 0;
};
