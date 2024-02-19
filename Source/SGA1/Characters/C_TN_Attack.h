// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_TN_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SGA1_API UC_TN_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UC_TN_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
