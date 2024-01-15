// Fill out your copyright notice in the Description page of Project Settings.

#include "C_AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "C_Character.h"

#include "CppMacro.h"

void UC_AnimInstance::NativeBeginPlay()
{
	Owner = Cast<AC_Character>(TryGetPawnOwner());
}

void UC_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Owner) return;

	Speed = Owner->GetVelocity().Size2D();
	bIsAir = Owner->GetCharacterMovement()->IsFalling();
	bEquipWeapon = Owner->GetbEquipWeapon();
	Velocity = Owner->GetVelocity();
	FRotator Rotator = Owner->GetActorRotation();
	Velocity = UKismetMathLibrary::InverseTransformDirection(FTransform(Rotator), Velocity);

	PlayerWeaponState = (int)(Owner->GetPlayerWeaponState());
}