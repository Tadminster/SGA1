// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_BTTaskNode_Patrol.h"

#include "C_AIController.h"
#include "Characters/C_Enemy.h"
#include "Components/C_PatrolComponent.h"

#include "CppMacro.h"

UC_BTTaskNode_Patrol::UC_BTTaskNode_Patrol()
{
	NodeName = "Patrol";
	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			UC_PatrolComponent* Patrol = CppMacro::GetComponent<UC_PatrolComponent>(OwnerEnemy);
			if (Patrol)
			{
				FVector Location; float AcceptanceRadius;
				// 다음 순찰 지점을 가져옴
				if (Patrol->GetNextPatrolPoint(Location, AcceptanceRadius))
				{
					return EBTNodeResult::InProgress;
				}
			}
		}
	}

	// 실패
	return EBTNodeResult::Failed;
}

void UC_BTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());
	UE_LOG(LogTemp, Log, TEXT("1"));
	if (AIController)
	{
		UE_LOG(LogTemp, Log, TEXT("2"));
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			UE_LOG(LogTemp, Log, TEXT("3"));
			UC_PatrolComponent* Patrol = CppMacro::GetComponent<UC_PatrolComponent>(OwnerEnemy);
			if (Patrol)
			{
				UE_LOG(LogTemp, Log, TEXT("4"));
				FVector Location; float AcceptanceRadius;
				if (Patrol->GetNextPatrolPoint(Location, AcceptanceRadius))
				{
					UE_LOG(LogTemp, Log, TEXT("5"));
					EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(Location, AcceptanceRadius, false);

					if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
					{
						UE_LOG(LogTemp, Log, TEXT("6-1"));
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						Patrol->UpdatePatrolPointIndex();
					}
					else if (Result == EPathFollowingRequestResult::Failed)
					{
						UE_LOG(LogTemp, Log, TEXT("6-2"));
						FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
					}
					else if (Result == EPathFollowingRequestResult::RequestSuccessful)
					{
						UE_LOG(LogTemp, Log, TEXT("6-3"));

					}
				}
			}
		}
	}
}
	