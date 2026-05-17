// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DeclutteringCharacter.generated.h"

class AMyPlayerState;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AItemsBase;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ADeclutteringCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ADeclutteringCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int Money = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	TArray<AItemsBase*> DropAndKeep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	int CaughtCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	bool hasBonus = true;

	// 有没有自己保留的东西
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Data")
	bool hasKeep = false;

	UFUNCTION(BlueprintCallable)
	void OnKeepResultCome(AItemsBase* Item, bool bCaught, int32 MoneyChanged);

	UFUNCTION(BlueprintCallable)
	void OnSortResultCome(AItemsBase* Item, bool bWasCorrect, int32 MoneyChanged);

	UFUNCTION(BlueprintCallable)
	void OnDropResultCome(AItemsBase* Item, bool bWasCorrect, int32 MoneyChanged);
protected:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
			

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY()
	TArray<AActor*> AllItems;

	UPROPERTY()
	AMyPlayerState* MyPlayerState = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowKeepResultUI(bool bCaught, int32 MoneyChanged);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowOperationDoneUI();
};

