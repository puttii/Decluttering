// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

#include "MyGameInstance.h"
#include "MyPlayerState.h"
#include "Decluttering/Items/ItemsBase.h"
#include "Decluttering/DeclutteringCharacter.h"
#include "Kismet/GameplayStatics.h"



void AMyGameMode::SetCaughtTimes(int NewCount)
{
	CaughtTimes = NewCount;
	if (CaughtTimes >3)
	{
		StealCaughtChance = 0.5;
	}
	if (CaughtTimes > 5)
	{
		StealCaughtChance = 0.6;
	}
}

void AMyGameMode::InitializeAllItems()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemsBase::StaticClass(), AllItems);
	NumsOfItems = AllItems.Num();
}

void AMyGameMode::InitializeGameData()
{
	if (hasInitializeAllItems)	return;
	hasInitializeAllItems = true;
	InitializeAllItems();
}

bool AMyGameMode::CanEndCurrentLevel()
{
	InitializeGameData();
	for (AActor* Actor : AllItems)
	{
		AItemsBase* Item = Cast<AItemsBase>(Actor);
		if (!Item->bProcessed)	return false;
	}
	return true;
}

void AMyGameMode::EndCurrentLevel()
{
	//UI显示
	ShowEndLevelUI();
}

void AMyGameMode::Upgrade()
{
	if (hasUpgrade)
	{
		// UI显示无法变废为宝
		OnHasUpgrade.Broadcast();
		return;
	}
	hasUpgrade = true;
	
	for (AActor* Actor : UpgradeCandidates)
	{
		AItemsBase* Item = Cast<AItemsBase>(Actor);
		int delta = Item->UpgradeItemValue - Item->ItemValue;
		ADeclutteringCharacter* PlayerChar = Cast<ADeclutteringCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if(PlayerChar)
		{
			PlayerChar->Money += delta;
			PlayerChar->MyGameInstance->SetTotalMoney(delta + PlayerChar->MyGameInstance->GetTotalMoney());
		}
	}
}


