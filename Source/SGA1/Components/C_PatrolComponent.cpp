// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_PatrolComponent.h"
#include "Components/SplineComponent.h"
#include "Characters/C_PatrolPath.h"

#include "CppMacro.h"

// Sets default values for this component's properties
UC_PatrolComponent::UC_PatrolComponent()
{

}

bool UC_PatrolComponent::GetNextPatrolPoint(FVector& OutPatrolPoint, float& AcceptanceRadius) const
{
	if (PatrolPath == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PatrolPath is nullptr"));
		return false;
	}

	OutPatrolPoint = PatrolPath->GetSplineComponent()->GetLocationAtSplinePoint(CurrentPatrolPointIndex, ESplineCoordinateSpace::World);
	AcceptanceRadius = PatrolPath->GetAcceptanceRadius();

	return true;
}

void UC_PatrolComponent::UpdatePatrolPointIndex()
{
	UE_LOG(LogTemp, Log, TEXT("UpdatePatrolPointIndex)"));
	if (PatrolPath == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PatrolPath is nullptr"));
		return;
	}

	// Get the number of points in the spline
	int32 NumberOfSplinePoints = PatrolPath->GetSplineComponent()->GetNumberOfSplinePoints();

	UE_LOG(LogTemp, Log, TEXT("Index: %d"), CurrentPatrolPointIndex);

	if (!bReversePatrol) // 沥规氢
	{
		UE_LOG(LogTemp, Log, TEXT("沥规氢"));
		if (CurrentPatrolPointIndex < NumberOfSplinePoints)
		{
			CurrentPatrolPointIndex++;
		}
		else
		{
			if (PatrolPath->GetSplineComponent()->IsClosedLoop())
			{
				// If the spline is a closed loop, reset the index to 0
				// 0 > 1 > 2 > 3 > 0 > 1 ...
				CurrentPatrolPointIndex = 0;
			}
			else
			{
				// If the spline is not a closed loop, reverse the patrol
				// 0 > 1 > 2 > 3 > 2 > 1 > 0 > 1 > 2 ...
				//CurrentPatrolPointIndex = NumberOfSplinePoints - 2;
				bReversePatrol = true;
			}
		}
	}
	else // 开规氢
	{
		UE_LOG(LogTemp, Log, TEXT("开规氢"));
		if (CurrentPatrolPointIndex > 0)
		{
			CurrentPatrolPointIndex--;
		}
		else
		{
			if (PatrolPath->GetSplineComponent()->IsClosedLoop())
			{
				// If the spline is a closed loop, reset the index to the last point
				// 0 > 1 > 2 > 3 > 0 > 1 ...
				CurrentPatrolPointIndex = NumberOfSplinePoints - 1;
			}
			else
			{
				// If the spline is not a closed loop, reverse the patrol
				// 0 > 1 > 2 > 3 > 2 > 1 > 0 > 1 > 2 ...
				bReversePatrol = false;
			}
		}
	}
}


// Called when the game starts
void UC_PatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



