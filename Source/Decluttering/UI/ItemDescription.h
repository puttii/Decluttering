// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Decluttering/Items/ItemsBase.h"
#include "ItemDescription.generated.h"

enum class EItemAction : uint8;
/**
 * 
 */
UCLASS()
class DECLUTTERING_API UItemDescription : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void HidePickupMessage();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowPickupMessage(const FText& ItemDescription);

	UFUNCTION(BlueprintCallable)
	void BroadCastPickupEvent(EItemAction Action);
};
