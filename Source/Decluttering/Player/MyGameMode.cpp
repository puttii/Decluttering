// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

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
