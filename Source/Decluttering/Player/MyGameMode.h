// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DECLUTTERING_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	float StealCaughtChance = 0.4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int CaughtTimes = 0;

	UFUNCTION()
	void SetCaughtTimes(int NewCount);

	UFUNCTION()
	int GetCaughtTimes(){ return CaughtTimes; };
};
