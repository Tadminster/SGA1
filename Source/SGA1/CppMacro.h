#pragma once
#include "CoreMinimal.h"

namespace CppMacro
{
	template <typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static T* GetComponent(AActor* InActor, FString InComponentName)
	{
		TArray<T*> Components;
		InActor->GetComponents<T>(Components);

		for (T* Component : Components)
		{
			if (Component->GetName() == InComponentName)
				return Component;
		}

		return NULL;
	}

	template<typename T>
	static void CreateComponent(AActor* Actor, T*& Component, const FName& Name, USceneComponent* Parent = nullptr)
	{
		Component = Actor->CreateDefaultSubobject<T>(Name);

		if (Parent) Component->SetupAttachment(Parent);
		else Actor->SetRootComponent(Component);
	}

	template<typename T>
	static void CreateActorComponent(AActor* Actor, T*& Component, const FName& Name)
	{
		Component = Actor->CreateDefaultSubobject<T>(Name);
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, const FString& Path)
	{
		ConstructorHelpers::FClassFinder<T> ClassFinder(*Path);

		//verifyf(asset.Succeeded(), L"Succeeded")
		if (ClassFinder.Succeeded()) *OutClass = ClassFinder.Class;
		else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *Path);
	}

	template<typename T>
	static void GetObject(T*& Asset, const FString& Path)
	{
		ConstructorHelpers::FObjectFinder<T> ObjectFinder(*Path);

		if (ObjectFinder.Succeeded()) Asset = ObjectFinder.Object;
		else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Asset: %s"), *Path);
	}

	template<typename T>
	static void GetAssetDynamic(T*& AssetObject, const FString& Path)
	{
		T Obj = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *Path));

		//verifyf(Obj, L"Succeeded")
		if (Obj) AssetObject = Obj;
		else UE_LOG(LogTemp, Warning, TEXT("Failed to Get AssetDynamic: %s"), *Path);
	}
}

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"