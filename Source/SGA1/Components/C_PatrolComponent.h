// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PatrolComponent.generated.h"

class AC_PatrolPath;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA1_API UC_PatrolComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	int32 CurrentPatrolPointIndex{ 0 };

	UPROPERTY(EditAnywhere)
	bool bReversePatrol{ false };

	// How close the AI needs to be to the next patrol point to move to the next one
	//UPROPERTY(EditAnywhere)
	//float AcceptanceRadius{ 50.0f }; 

public:
	UPROPERTY(EditAnywhere, Category = "Path")
	AC_PatrolPath* PatrolPath;

public:	
	// Sets default values for this component's properties
	UC_PatrolComponent();

	FORCEINLINE bool IsValidPatrolPath() const { return PatrolPath != nullptr; }
	bool GetNextPatrolPoint(FVector& OutPatrolPoint, float& AcceptanceRadius) const;

	// 다음에 갈 PatrolPoint의 Index를 업데이트
	void UpdatePatrolPointIndex();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
		
};
