// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDescription.h"
#include "Decluttering/Player/MyPlayerController.h"

void UItemDescription::BroadCastPickupEvent(EItemAction Action)
{
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	AItemsBase* ThisActor = PlayerController->ThisActor.Get();
	ThisActor->ItemPickedUp(Action);
}
