// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "CppMacro.h"

AC_GameModeBase::AC_GameModeBase()
{
	// Set this class to be the default pawn class
	FString Path = TEXT("Blueprint'/Game/Scene2/BP_Character.BP_Character_C'");
	CppMacro::GetClass(&DefaultPawnClass, Path);
}
