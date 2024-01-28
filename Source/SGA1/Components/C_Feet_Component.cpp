// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_Feet_Component.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UC_Feet_Component::UC_Feet_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//void UC_Feet_Component::TraceFeet(FName _SocketName, FVector& OutDistance)
//{
//	FVector Start = GetOwner()->GetActorLocation();
//	FVector End = Start + FVector(0, 0, -1000);
//
//	FHitResult HitResult;
//	FCollisionQueryParams Params;
//	Params.AddIgnoredActor(GetOwner());
//
//	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
//	{
//		OutDistance = HitResult.ImpactPoint;
//	}
//	else
//	{
//		OutDistance = FVector(0, 0, 0);
//	}
//}

void UC_Feet_Component::TraceFeet(FName _SocketName, float& OutDistance)
{
	OutDistance = 0.0f;

	FVector Location = OwnerCharacter->GetMesh()->GetSocketLocation(_SocketName);
	FVector Start = FVector(Location.X, Location.Y, OwnerCharacter->GetActorLocation().Z);
	float TraceZ = Start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector End = FVector(Location.X, Location.Y, TraceZ);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActors(ActorsToIgnore);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		OutDistance = HitResult.Distance;
	}
	else
	{
		OutDistance = 0.0f;
	}


}


// Called when the game starts
void UC_Feet_Component::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}


// Called every frame
void UC_Feet_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float LeftFootDistance;
	float RightFootDistance;

	TraceFeet("LeftFootSocket", LeftFootDistance);
	TraceFeet("RightFootSocket", RightFootDistance);

	FeetData.LeftFootLocation = OwnerCharacter->GetMesh()->GetSocketLocation(LeftFootSocketName);
	FeetData.RightFootLocation = OwnerCharacter->GetMesh()->GetSocketLocation(RightFootSocketName);

	FeetData.LeftFootLocation.Z += LeftFootDistance;
	FeetData.RightFootLocation.Z += RightFootDistance;

	//UE_LOG(LogTemp, Warning, TEXT("Left Foot Distance: %f"), LeftFootDistance);
	//UE_LOG(LogTemp, Warning, TEXT("Right Foot Distance: %f"), RightFootDistance);

}

