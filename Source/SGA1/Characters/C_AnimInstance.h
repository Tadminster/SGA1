// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SGA1_API UC_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	class AC_Character* Owner{nullptr};

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bIsAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bEquipWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector	Velocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int		PlayerWeaponState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator Rotator;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)



public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
