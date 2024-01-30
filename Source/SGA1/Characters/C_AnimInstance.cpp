// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/C_AnimInstance.h"
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
	FRotator TempRotator = Owner->GetActorRotation();
	Velocity = UKismetMathLibrary::InverseTransformDirection(FTransform(TempRotator), Velocity);

	PlayerWeaponState = (int)(Owner->GetPlayerWeaponState());

	// 총기 방향 보간
	{
		FRotator TempTarget = UKismetMathLibrary::NormalizedDeltaRotator(Owner->GetControlRotation(), Owner->GetActorRotation());
		TempTarget.Yaw = UKismetMathLibrary::ClampAngle(TempTarget.Yaw, -90.f, 90.f);
		TempTarget.Pitch = UKismetMathLibrary::ClampAngle(TempTarget.Pitch, -90.f, 90.f);

		Rotator.Yaw = UKismetMathLibrary::ClampAngle(Rotator.Yaw, -90.f, 90.f);
		Rotator.Pitch = UKismetMathLibrary::ClampAngle(Rotator.Pitch, -90.f, 90.f);

		Rotator.Yaw = UKismetMathLibrary::FInterpTo(Rotator.Yaw, TempTarget.Yaw, DeltaSeconds, 10.f);
		Rotator.Pitch = UKismetMathLibrary::FInterpTo(Rotator.Pitch, TempTarget.Pitch, DeltaSeconds, 10.f);
	}
}