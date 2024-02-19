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
	AC_Enemy*				OwnerEnemy;				// AI ������
	UAISenseConfig_Sight*	SightConfig;			// AI �þ� ����
	UAIPerceptionComponent* PerceptionComponent;	// ���� ������Ʈ
	UBlackboardComponent*	BlackboardComponent;	// ������ ������Ʈ


protected:
	// �����Ϳ��� �����ų ������

	// AI�� �ൿ ���¸� �����ϴ� Ű
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName BehaviorStateKey = "BehaviorState";

	// AI�� Ÿ���� �����ϴ� Ű
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName TargetKey = "Target";
	
	// AI�� ����	�� �� �ִ� ����
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//float BehaviorRange = 200.0f;

	// AI�� �þ߿� ���̴��� üũ�ϴ� �Լ�
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
	virtual void		OnPossess(APawn* InPawn) override;			// AI�� Possess(����)�� �� ȣ��Ǵ� �Լ�
	virtual void		OnUnPossess() override;						// AI�� UnPossess(���� ����)�� �� ȣ��Ǵ� �Լ�

	FORCEINLINE FName	GetTargetKey() const { return TargetKey; };	// Ÿ�� Ű�� ��ȯ�ϴ� �Լ�
	AC_Player*			GetTargetPlayer() const;					// Ÿ�� �÷��̾ ��ȯ�ϴ� �Լ�
	EBeHaviorState		GetState() const;							// ���� �ൿ ���¸� ��ȯ�ϴ� �Լ�
	
	void				SetState(EBeHaviorState NewState);			// �ൿ ���¸� �����ϴ� �Լ�
	void				SetSightConfig(float SightRadius, float LoseSightRadius, float PeripheralVisionAngleDegrees);	// �þ� ������ �����ϴ� �Լ�

private:
	UFUNCTION() // AI �þ߿� ���̴��� üũ�ϴ� �Լ�
		void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

};
