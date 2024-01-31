// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_AIController.generated.h"


UENUM(BlueprintType)
enum class EBeHaviorState : uint8
{
	Idle, Patrol, Chase, Attack
};


class AC_Enemy;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class SGA1_API AC_AIController : public AAIController
{
	GENERATED_BODY()
	
private:
	AC_Enemy* OwnerEnemy; // AI 소유자
	UAISenseConfig_Sight* SightConfig; // AI 시야 설정
	UAIPerceptionComponent* PerceptionComponent; // 인지 컴포넌트


protected:
	// 에디터에서 노출시킬 변수들

	// AI의 행동 상태를 저장하는 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName BehaviorStateKey = "BehaviorState";

	// AI의 타겟을 저장하는 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName TargetKey = "Target";
	
	// AI가 시야에 보이는 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float BehaviorRange = 500.0f;

	// AI가 시야에 보이는지 체크하는 함수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bDrawDebugSightSphere = true;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AdjustSightRadius = 100.0f;
	

private:
	UFUNCTION() // AI 시야에 보이는지 체크하는 함수
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

public:
	AC_AIController();

	FORCEINLINE AC_Enemy* GetOwnerEnemy() const { return OwnerEnemy; }
	float GetAiSightRadius() const;
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override; // AI를 Possess(빙의)할 때 호출되는 함수
	virtual void OnUnPossess() override;			// AI를 UnPossess(빙의 해제)할 때 호출되는 함수

};
