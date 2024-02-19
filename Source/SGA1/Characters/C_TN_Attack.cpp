// Fill out your copyright notice in the Description page of Project Settings.
#include "Characters/C_TN_Attack.h"

#include "C_AIController.h"
#include "Characters/C_Enemy.h"

#include "CppMacro.h"

UC_TN_Attack::UC_TN_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}

// 테스크가 실행될 때 한번 호출되는 함수
EBTNodeResult::Type UC_TN_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			// 공격
			OwnerEnemy->Attack();
		}
	}


	return EBTNodeResult::InProgress;
}

// 테스크가 실행되는 동안 계속 호출되는 함수
void UC_TN_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			// 공격이 끝났는지 확인
			if (OwnerEnemy->IsAttackEnd())
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}
