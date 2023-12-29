#pragma once
#include "CoreMinimal.h"

namespace CppMacro
{
	template<typename T>
	static void CreateComponet(AActor* Actor, T*& Component, const FName& Name, USceneComponent* Parent = nullptr)
	{
		Component = Actor->CreateDefaultSubobject<T>(Name);

		if (Parent) Component->SetupAttachment(Parent);
		else Actor->SetRootComponent(Component);
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, const FString& Path)
	{
		ConstructorHelpers::FClassFinder<T> asset(*Path);

		//verifyf(asset.Succeeded(), L"Succeeded")
		if (asset.Succeeded()) *OutClass = asset.Class;
		else UE_LOG(LogTemp, Warning, TEXT("Failed to Get Class: %s"), *Path);
	}

	static void GetAsset(UStaticMesh*& Asset, const FString& Path)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(*Path);
		
		//verifyf(asset.Succeeded(), L"Succeeded")
		if (asset.Succeeded()) Asset = asset.Object;
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