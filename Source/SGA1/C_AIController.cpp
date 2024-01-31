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

	SightConfig->SightRadius = 1000.0f;		// �þ� �Ÿ�
	SightConfig->LoseSightRadius = 1200.0f;	// �þ߸� �Ҵ� �Ÿ�
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;	// �þ߰� (������� 60�� = �¿�120��)
	SightConfig->SetMaxAge(5.0f);			// �þ߰� ������� �ð� (5�� �ڿ� �����)

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
	TArray<AActor*> Enemies; // �� �迭

	// ���� �νĵ� ������ Enemies �迭�� ����
	// nullptr�� ������ ��� ���� ����
	PerceptionComponent->GetCurrentlyPerceivedActors(nullptr, Enemies); 



}