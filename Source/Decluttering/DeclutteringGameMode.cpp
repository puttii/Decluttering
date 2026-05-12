// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeclutteringGameMode.h"
#include "DeclutteringCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeclutteringGameMode::ADeclutteringGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
