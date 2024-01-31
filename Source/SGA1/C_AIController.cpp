// Fill out your copyright notice in the Description page of Project Settings.


#include "C_AIController.h"
#include "Characters/C_Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "DrawDebugHelpers.h"

#include "CppMacro.h"



AC_AIController::AC_AIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CppMacro::CreateActorComponet<UAIPerceptionComponent>(this, PerceptionComponent, "PerceptionComponent");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1000.0f;		// 시야 거리
	SightConfig->LoseSightRadius = 1200.0f;	// 시야를 잃는 거리
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;	// 시야각 (정면기준 60도 = 좌우120도)
	SightConfig->SetMaxAge(5.0f);			// 시야가 사라지는 시간 (5초 뒤에 사라짐)

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
		float Radius = SightConfig->SightRadius + AdjustSightRadius;

		//DrawDebugSphere(GetWorld(), Center, Radius, 16, FColor::Red, false, 0.0f, 0, 1.0f);
		//DrawDebugSphere(GetWorld(), Center, BehaviorRange, 16, FColor::Red, false, 0.0f, 0, 1.0f);

		DrawDebugCircle(GetWorld(), Center, BehaviorRange, 16, FColor::Red, false, 0.0f, 0, 1.0f);
	}
}

void AC_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	OwnerEnemy = Cast<AC_Enemy>(InPawn);

	if (OwnerEnemy)
	{
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AC_AIController::OnPerceptionUpdated);
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

void AC_AIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> Enemies; // 적 배열

	// 현재 인식된 적들을 Enemies 배열에 넣음
	// nullptr을 넣으면 모든 적을 넣음
	PerceptionComponent->GetCurrentlyPerceivedActors(nullptr, Enemies); 



}