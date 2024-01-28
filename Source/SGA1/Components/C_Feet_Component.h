// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_Feet_Component.generated.h"

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector LeftFootLocation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		FVector RightFootLocation;
};

class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA1_API UC_Feet_Component : public UActorComponent
{
	GENERATED_BODY()

private:
	ACharacter* OwnerCharacter;
	FFeetData*	FeetData;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName LeftFootSocketName{ "ik_foot_l" };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName RightFootSocketName{ "ik_foot_r" };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float TraceDistance{ 100.f };

public:	
	// Sets default values for this component's properties
	UC_Feet_Component();

private:
	//void TraceFeet(FName _SocketName, FVector& OutDistance);
	void TraceFeet(FName _SocketName, float& OutDistance);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE FFeetData& GetFeetData() const { return *FeetData; }
};
