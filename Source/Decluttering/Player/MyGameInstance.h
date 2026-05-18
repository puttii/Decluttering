// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DECLUTTERING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int TotalMoney = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int Credit = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int Bonus = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	bool hasBonus = true;

	void SetCredit(int InCredit){ Credit = InCredit; };
	int GetCredit(){ return Credit; };

	void SetTotalMoney(int InTotalMoney){ TotalMoney = InTotalMoney; };
	int GetTotalMoney(){ return TotalMoney; };
};
