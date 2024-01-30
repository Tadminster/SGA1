// Fill out your copyright notice in the Description page of Project Settings.


#include "C_GameModeBase.h"
#include "CppMacro.h"

AC_GameModeBase::AC_GameModeBase()
{
	// Set this class to be the default pawn class
	FString Path = TEXT("/Script/Engine.Blueprint'/Game/Scene2/Characters/BP_Player.BP_Player_C'");
	CppMacro::GetClass(&DefaultPawnClass, Path);

}
