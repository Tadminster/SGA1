// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTaskNode_SetMovementSpeed.generated.h"

UENUM(BlueprintType)
enum class EEnemyMovementSpeed : uint8
{
	Walk UMETA(DisplayName = "Walk", ToolTip = "Movement Speed 200"),
	Run UMETA(DisplayName = "Run", ToolTip = "Movement Speed 600"),
	Size UMETA(DisplayName = "Size", ToolTip = "Enum Size Check")
};

/**
 * 
 */
UCLASS()
class SGA1_API UC_BTTaskNode_SetMovementSpeed : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float Speed[(int32)EEnemyMovementSpeed::Size] = { 200.0f, 600.0f };

	UPROPERTY(EditAnywhere)
	EEnemyMovementSpeed MovementState;

public:
	UC_BTTaskNode_SetMovementSpeed();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
