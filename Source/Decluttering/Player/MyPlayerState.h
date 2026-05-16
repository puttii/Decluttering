// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DECLUTTERING_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int TotalMoney = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int Credit = 100;	
};
