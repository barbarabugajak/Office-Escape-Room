// Copyright Epic Games, Inc. All Rights Reserved.

#include "Escape_Room_GameGameMode.h"
#include "Escape_Room_GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscape_Room_GameGameMode::AEscape_Room_GameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
