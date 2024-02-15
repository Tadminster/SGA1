// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DrawDebugHelpers.h"

#include "Characters/C_Enemy.h"
#include "Characters/C_Player.h"

#include "CppMacro.h"



AC_AIController::AC_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateActorComponet<UAIPerceptionComponent>(this, PerceptionComponent, TEXT("PerceptionComponent"));
	CppMacro::CreateActorComponet<UBlackboardComponent>(this, BlackboardComponent, TEXT("BlackboardComponent"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1000.0f;		// �þ� �Ÿ�
	SightConfig->LoseSightRadius = 1400.0f;	// �þ߸� �Ҵ� �Ÿ�
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;	// �þ߰� (������� 60�� = �¿�120��)
	SightConfig->SetMaxAge(3.0f);			// �þ߰� ������� �ð� (3�� �ڿ� �����)

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;		// �� ����
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;	// �Ʊ� ����
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;	// �߸� ����

	PerceptionComponent->ConfigureSense(*SightConfig); // ���� ���� ����
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation()); // �켱 ���� ����
}

float AC_AIController::GetAiSightRadius() const
{
	return SightConfig->SightRadius;
}

void AC_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AC_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDrawDebugSightSphere)
	{
		FVector Center = GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector() * AdjustSightRadius;

		DrawDebugSphere(GetWorld(), Center, BehaviorRange, 16, FColor::Red, false, 0.0f, 0, 1.0f);
		//DrawDebugCircle(GetWorld(), Center, BehaviorRange, 16, FColor::Red, false, 0.0f, 0, 0, FVector::RightVector, FVector::ForwardVector);
	}
}

void AC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<AC_Enemy>(InPawn);

	if (OwnerEnemy)
	{
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AC_AIController::OnPerceptionUpdated);

		UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, BlackboardComponent);
		RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
	}
}

void AC_AIController::OnUnPossess()
{
	Super::OnUnPossess();

	//Clear
	if (OwnerEnemy)
	{
		PerceptionComponent->OnPerceptionUpdated.Clear();
		//PerceptionComponent->OnPerceptionUpdated.RemoveDynamic(this, &AC_AIController::OnPerceptionUpdated);
	}
}

AC_Player* AC_AIController::GetTargetPlayer() const
{
	return Cast<AC_Player>(Blackboard->GetValueAsObject(TargetKey));
}

EBeHaviorState AC_AIController::GetState() const
{
	return (EBeHaviorState)Blackboard->GetValueAsEnum(BehaviorStateKey);
}

void AC_AIController::SetState(EBeHaviorState NewState)
{
	Blackboard->SetValueAsEnum(BehaviorStateKey, (uint8)NewState);
}

void AC_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> Enemies; // �� �迭

	// ���� �νĵ� ������ Enemies �迭�� ����
	// nullptr�� ������ ��� ���� ����
	PerceptionComponent->GetCurrentlyPerceivedActors(nullptr, Enemies); 

	// ���� ����� ���� ã��
	AC_Player* TargetPlayer = nullptr;
	for (AActor* Actor : Enemies)
	{
		TargetPlayer = Cast<AC_Player>(Actor);
		if (TargetPlayer) break;
	}

	// �����忡 Ÿ�� �÷��̾ ����
	Blackboard->SetValueAsObject(TargetKey, TargetPlayer);
}