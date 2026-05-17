// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */

class AItemsBase;
class UItemDescription;

UCLASS()
class DECLUTTERING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void TraceForItem();
	
	UPROPERTY(EditDefaultsOnly)
	double TraceLength;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UItemDescription> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UItemDescription> HUDWidget;

	TWeakObjectPtr<AItemsBase> ThisActor;
	TWeakObjectPtr<AItemsBase> LastActor;
	
};
