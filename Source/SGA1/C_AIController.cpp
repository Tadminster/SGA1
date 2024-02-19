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

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;		// 적 감지
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;	// 아군 감지
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;	// 중립 감지

	PerceptionComponent->ConfigureSense(*SightConfig); // 감지 설정 적용
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation()); // 우선 감지 설정
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

		DrawDebugSphere(GetWorld(), Center, OwnerEnemy->MeleeRange, 16, FColor::Red, false, 0.0f, 0, 1.0f);
		//DrawDebugCircle(GetWorld(), Center, BehaviorRange, 16, FColor::Red, false, 0.0f, 0, 0, FVector::RightVector, FVector::ForwardVector);
	}
}

void AC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<AC_Enemy>(InPawn);

	if (OwnerEnemy)
	{

		SetSightConfig(OwnerEnemy->SightRadius, OwnerEnemy->LoseSightRadius, OwnerEnemy->PeripheralVisionAngleDegrees);

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

void AC_AIController::SetSightConfig(float SightRadius, float LoseSightRadius, float PeripheralVisionAngleDegrees)
{
	SightConfig->SightRadius = SightRadius;				// 시야 범위
	SightConfig->LoseSightRadius = LoseSightRadius;		// 시야 잃는 범위
	SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;	// 시야 각도
	SightConfig->SetMaxAge(3.0f);						// 시야가 사라지는 시간 (3초 뒤에 사라짐)
	
	PerceptionComponent->ConfigureSense(*SightConfig);	// 감지 설정 적용
}

void AC_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> Enemies; // 적 배열

	// 현재 인식된 적들을 Enemies 배열에 넣음
	// nullptr을 넣으면 모든 적을 넣음
	PerceptionComponent->GetCurrentlyPerceivedActors(nullptr, Enemies); 

	// 가장 가까운 적을 찾음
	AC_Player* TargetPlayer = nullptr;
	for (AActor* Actor : Enemies)
	{
		TargetPlayer = Cast<AC_Player>(Actor);
		if (TargetPlayer) break;
	}

	// 블랙보드에 타겟 플레이어를 넣음
	Blackboard->SetValueAsObject(TargetKey, TargetPlayer);
}