// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_Melee.generated.h"

/**
 * 
 */
UCLASS()
class SGA1_API UC_BTS_Melee : public UBTService
{
	GENERATED_BODY()
	
public:
	UC_BTS_Melee();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
