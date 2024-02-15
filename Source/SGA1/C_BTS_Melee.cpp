// Fill out your copyright notice in the Description page of Project Settings.


#include "C_BTS_Melee.h"
#include "C_AIController.h"

#include "Characters/C_Enemy.h"
#include "Characters/C_Player.h"

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
			AC_Player* TargetPlayer = Cast<AC_Player>(AIController->GetBlackboardComponent()->GetValueAsObject(AIController->GetTargetKey()));

			if (!TargetPlayer)
			{
				AIController->SetState(EBeHaviorState::Idle);
				return;
			}

			float Distance = OwnerEnemy->GetDistanceTo(TargetPlayer);
			if (Distance <= OwnerEnemy->MeleeDistance)
			{
				AIController->SetState(EBeHaviorState::Attack);
				//Enemy->MeleeAttack();

				return;
			}
			else
			{
				AIController->SetState(EBeHaviorState::Chase);
				return;
			}
		}
	}
}
