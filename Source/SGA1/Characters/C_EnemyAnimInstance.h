// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SGA1_API UC_EnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	class AC_Enemy* Owner{ nullptr };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Speed;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
