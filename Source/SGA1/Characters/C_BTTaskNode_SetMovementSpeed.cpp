// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_BTTaskNode_SetMovementSpeed.h"

#include "C_AIController.h"
#include "Characters/C_Enemy.h"
#include "Components/C_PatrolComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CppMacro.h"

UC_BTTaskNode_SetMovementSpeed::UC_BTTaskNode_SetMovementSpeed()
{
	NodeName = TEXT("Set Movement Speed");
}

EBTNodeResult::Type UC_BTTaskNode_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			UCharacterMovementComponent* MovementComponent = OwnerEnemy->GetCharacterMovement();
			MovementComponent->MaxWalkSpeed = Speed[(int32)MovementState];
		}
	}

	return EBTNodeResult::Type();
}
