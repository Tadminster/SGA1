#pragma once
#include "CoreMinimal.h"

namespace CppMacro
{
	template<typename T>
	static void CreateComponet(AActor* Actor, T*& Component, const FName Name, USceneComponent* Parent = nullptr)
	{
		Component = Actor->CreateDefaultSubobject<T>(Name);

		if (Parent) Component->SetupAttachment(Parent);
		else Actor->SetRootComponent(Component);
	}

	static void GetAsset(UStaticMesh*& Asset, const FString Path)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(*Path);
		
		if (asset.Succeeded())
		{
			Asset = asset.Object;
		}
	}
}