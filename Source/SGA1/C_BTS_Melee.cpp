// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTS_Melee.h"
#include "C_AIController.h"

#include "Characters/C_Enemy.h"
#include "Characters/C_Player.h"
#include "Components/C_PatrolComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "CppMacro.h"

UC_BTS_Melee::UC_BTS_Melee()
{
	NodeName = TEXT("Melee");

}

void UC_BTS_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetOwner());
	AC_AIController* AIController = Cast<AC_AIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AC_Enemy* OwnerEnemy = Cast<AC_Enemy>(AIController->GetPawn());
		if (OwnerEnemy)
		{
			// 타겟 플레이어 확인
			AC_Player* TargetPlayer = Cast<AC_Player>(AIController->GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));
			if (!TargetPlayer) // 타겟이 없을 경우
			{
				// 패트롤 확인
				UC_PatrolComponent* Patrol = CppMacro::GetComponent<UC_PatrolComponent>(OwnerEnemy);
				if (Patrol && Patrol->IsValidPatrolPath()) // 패트롤 경로가 있을 경우
				{
					// 패트롤 상태로 변경
					AIController->SetState(EBeHaviorState::Patrol);
				}
				else
				{
					// 대기 상태로 변경
					AIController->SetState(EBeHaviorState::Idle);
				}

				return;
			}

			// 거리 계산 & 상태 변경
			float Distance = OwnerEnemy->GetDistanceTo(TargetPlayer);
			if (Distance <= OwnerEnemy->MeleeRange)
			{
				// 공격
				AIController->SetState(EBeHaviorState::Attack);
				//Enemy->MeleeAttack();

				return;
			}
			else if (Distance > OwnerEnemy->SightRadius)
			{
				// 추격
				AIController->SetState(EBeHaviorState::Chase);
				return;
			}
			else
			{
				// 대기
				AIController->SetState(EBeHaviorState::Chase);
				return;
			}
		}
	}
}
