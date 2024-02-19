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
class AC_Player;
class UAISenseConfig_Sight;
class UAIPerceptionComponent;
class UBlackboardComponent;


/**
 * 
 */
UCLASS()
class SGA1_API AC_AIController : public AAIController
{
	GENERATED_BODY()
	
private:
	AC_Enemy*				OwnerEnemy;				// AI 소유자
	UAISenseConfig_Sight*	SightConfig;			// AI 시야 설정
	UAIPerceptionComponent* PerceptionComponent;	// 인지 컴포넌트
	UBlackboardComponent*	BlackboardComponent;	// 블랙보드 컴포넌트


protected:
	// 에디터에서 노출시킬 변수들

	// AI의 행동 상태를 저장하는 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName BehaviorStateKey = "BehaviorState";

	// AI의 타겟을 저장하는 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName TargetKey = "Target";
	
	// AI가 공격	할 수 있는 범위
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//float BehaviorRange = 200.0f;

	// AI가 시야에 보이는지 체크하는 함수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bDrawDebugSightSphere = true;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AdjustSightRadius = 100.0f;
	



public:
	AC_AIController();

	FORCEINLINE AC_Enemy* GetOwnerEnemy() const { return OwnerEnemy; }
	float GetAiSightRadius() const;
	
	virtual void		Tick(float DeltaTime) override;
	virtual void		BeginPlay() override;
	virtual void		OnPossess(APawn* InPawn) override;			// AI를 Possess(빙의)할 때 호출되는 함수
	virtual void		OnUnPossess() override;						// AI를 UnPossess(빙의 해제)할 때 호출되는 함수

	FORCEINLINE FName	GetTargetKey() const { return TargetKey; };	// 타겟 키를 반환하는 함수
	AC_Player*			GetTargetPlayer() const;					// 타겟 플레이어를 반환하는 함수
	EBeHaviorState		GetState() const;							// 현재 행동 상태를 반환하는 함수
	
	void				SetState(EBeHaviorState NewState);			// 행동 상태를 설정하는 함수
	void				SetSightConfig(float SightRadius, float LoseSightRadius, float PeripheralVisionAngleDegrees);	// 시야 설정을 설정하는 함수

private:
	UFUNCTION() // AI 시야에 보이는지 체크하는 함수
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

};
