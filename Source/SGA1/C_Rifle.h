// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Rifle.generated.h"

UCLASS()
class SGA1_API AC_Rifle : public AActor
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
	UAnimMontage* EquipMontage2;

	// unequip montages
	UPROPERTY(EditAnywhere, Category = "Anim")
	UAnimMontage* UnequipMontage2;

	UPROPERTY(EditAnywhere)
	FName HandSocket{ TEXT("grabRifle") };

	UPROPERTY(EditAnywhere)
	FName BackSocket{ TEXT("sheath_spine_04") };


private:
	class ACharacter* OwnerCharacter;

public:	
	// Sets default values for this actor's properties
	AC_Rifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static AC_Rifle* Spawn(class ACharacter* Character);

	void Equip();
	void UnEquip();

	UFUNCTION(BlueprintCallable)
	void GrabRifle();
	UFUNCTION(BlueprintCallable)
	void BackRifle();
};
