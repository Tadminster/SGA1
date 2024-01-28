// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_WB_Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class SGA1_API UC_WB_Crosshair : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintImplementableEvent)
		void CrosshairVisible();

		UFUNCTION(BlueprintImplementableEvent)
		void CrosshairInvisible();

		UFUNCTION(BlueprintImplementableEvent)
		void EnemyInCrosshair();

		UFUNCTION(BlueprintImplementableEvent)
		void EnemyOutCrosshair();
};
