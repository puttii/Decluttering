// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameMode.generated.h"

class AItemsBase;



DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnHasUpgrade
);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	int NumsOfItems = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TArray<AItemsBase*> UpgradeCandidates;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TArray<AActor*> AllItems;

	UPROPERTY()
	bool hasInitializeAllItems = false;

	UFUNCTION()
	void SetCaughtTimes(int NewCount);

	UFUNCTION()
	int GetCaughtTimes(){ return CaughtTimes; }
	
	UFUNCTION()
	void InitializeAllItems();

	UFUNCTION()
	void InitializeGameData();

	UFUNCTION()
	bool CanEndCurrentLevel();

	UFUNCTION()
	void EndCurrentLevel();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEndLevelUI();

	UFUNCTION(BlueprintCallable)
	void Upgrade();

	UPROPERTY()
	bool hasUpgrade = false;

	UPROPERTY(BlueprintAssignable)
	FOnHasUpgrade OnHasUpgrade;
};
