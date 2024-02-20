// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_PatrolPath.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

#include "CppMacro.h"


// Sets default values
AC_PatrolPath::AC_PatrolPath()
{
	CppMacro::CreateComponent<USceneComponent>(this, SceneComponent, "SceneComponent");
	CppMacro::CreateComponent<USplineComponent>(this, SplineComponent, "SplineComponent", SceneComponent);
	CppMacro::CreateComponent<UTextRenderComponent>(this, TextRenderComponent, "TextRenderComponent", SceneComponent);

	// Set the text render component's text to the name of the actor
	TextRenderComponent->SetText(FText::FromString(GetName()));
	TextRenderComponent->SetTextRenderColor(FColor::Red);
	TextRenderComponent->SetHorizontalAlignment(EHTA_Center);
	TextRenderComponent->SetVerticalAlignment(EVRTA_TextCenter);
	//TextRenderComponent->SetWorldSize(100.0f);
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	TextRenderComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	TextRenderComponent->SetRelativeScale3D(FVector(2));

	// Set the spline component's location and rotation to the root component's location and rotation
	//SplineComponent->SetWorldLocation(GetActorLocation());
	//SplineComponent->SetWorldRotation(GetActorRotation());
	SplineComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));


}

void AC_PatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SplineComponent->SetClosedLoop(bClosedLoop);

	// Clear the patrol points array
	//PatrolPoints.Empty();

	// Get all the children of the patrol path
	//TArray<USceneComponent*> Children;
	//GetRootComponent()->GetChildrenComponents(true, Children);

	//// Loop through all the children
	//for (USceneComponent* Child : Children)
	//{
	//	// Cast the child to a scene component
	//	USceneComponent* SceneComponent = Cast<USceneComponent>(Child);

	//	// If the cast was successful
	//	if (SceneComponent)
	//	{
	//		// Add the scene component to the patrol points array
	//		PatrolPoints.Add(SceneComponent->GetComponentLocation());
	//	}
	//}
}

// Called when the game starts or when spawned
void AC_PatrolPath::BeginPlay()
{
	Super::BeginPlay();

}
