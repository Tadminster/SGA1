// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_EnemyAnimInstance.h"
#include "Characters/C_Enemy.h"

void UC_EnemyAnimInstance::NativeBeginPlay()
{
	Owner = Cast<AC_Enemy>(TryGetPawnOwner());
}

void UC_EnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Owner)
	{
		Speed = Owner->GetVelocity().Size2D();
		//bIsInAir = Owner->GetMovementComponent()->IsFalling();
		//bIsDead = Owner->IsDead();
	}
}
