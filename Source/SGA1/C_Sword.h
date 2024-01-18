// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Sword.generated.h"

class USkeletalMeshComponent;
class USceneComponent;

UCLASS()
class SGA1_API AC_Sword : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* SkeletalMesh;

public:
	// attack montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* AttackMontage;

	// equip montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* EquipMontage;

	// unequip montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditAnywhere)
	FName HandSocket{ TEXT("grabWeapon") };

	UPROPERTY(EditAnywhere)
	FName SheathSocket{ TEXT("sheath_thigh_l") };

private:
	class ACharacter* OwnerCharacter;

	int32	AttackCurStage;
	int32	AttackMaxStage;
	float	ComboTime;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool	bCanAttack{ true };


public:	
	// Sets default values for this actor's properties
	AC_Sword();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	static AC_Sword* Spawn(class ACharacter* Character);

	void Equip();
	void UnEquip();

	UFUNCTION(BlueprintCallable)
	void GrabSword();
	UFUNCTION(BlueprintCallable)
	void SheathSword();

	void Attack();			// LMB 기본공격
	void SpecialAction();	// RMB 특수행동 (미정)
};
