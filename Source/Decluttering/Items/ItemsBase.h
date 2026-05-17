// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemsBase.generated.h"

UENUM(BlueprintType)
enum class EItemAction : uint8
{
	Sort UMETA(DisplayName = "整理"),
	Drop UMETA(DisplayName = "丢弃"),
	Keep UMETA(DisplayName = "暂时保留")
};

UENUM(BlueprintType)
enum class EDamageLevel : uint8
{
	New UMETA(DisplayName = "全新"),
	Light UMETA(DisplayName = "轻度损坏"),
	Medium UMETA(DisplayName = "中度损坏"),
	Heavy UMETA(DisplayName = "重度损坏")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnItemProcessed,
	AItemsBase*, Item,
	EItemAction, PlayerAction
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnKeepResult,
	AItemsBase*, Item,
	bool, bCaught,
	int32, MoneyChanged
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnSortOrDropResult,
	AItemsBase*, Item,
	bool, bWasCorrect, 
	int32, MoneyChanged
);

UCLASS()
class DECLUTTERING_API AItemsBase : public AActor
{
	GENERATED_BODY()

public:
	AItemsBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* Mesh;

	// 物品名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText ItemName;

	// 使用年限
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 UseYears = 0;

	// 损坏程度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EDamageLevel DamageLevel = EDamageLevel::New;

	// 物品价格，不显示给玩家
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 ItemValue = 10;

	// 变废为宝后价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	int32 UpgradeItemValue = 20;

	// 正确处理方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	EItemAction CorrectAction = EItemAction::Keep;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	FText ItemDescription;
	
	// 是否已经处理过
	UPROPERTY(BlueprintReadOnly, Category = "Item State")
	bool bProcessed = false;

	// 玩家是否判断正确
	UPROPERTY(BlueprintReadOnly, Category = "Item State")
	bool bWasCorrect = false;

	// 玩家是否偷拿
	UPROPERTY(BlueprintReadOnly, Category = "Item State")
	bool bWasStolen = false;
	
	// Keep 结果事件, bCaught = 是否被发现
	// MoneyChanged = 成功时 +ItemValue，失败时 -ItemValue
	UPROPERTY(BlueprintAssignable, Category = "Item Event")
	FOnKeepResult OnKeepResult;
	// 整理委托
	UPROPERTY(BlueprintAssignable, Category = "Item Event")
	FOnSortOrDropResult OnSortResult;
	// 丢弃委托
	UPROPERTY(BlueprintAssignable, Category = "Item Event")
	FOnSortOrDropResult OnDropResult;

	// 玩家点击物品时调用
	UFUNCTION(BlueprintCallable, Category = "Item")
	void Interact();

	// 玩家选择 清理 / 保留 / 拿走
	UFUNCTION(BlueprintCallable, Category = "Item")
	void ProcessItem(EItemAction PlayerAction, float StealCaughtChance);

	// 获取物品信息文本，方便 UI 显示
	UFUNCTION(BlueprintCallable, Category = "Item")
	FText GetItemInfoText() const;

	// 当前物品是否可以再次交互
	UFUNCTION(BlueprintCallable, Category = "Item")
	bool CanInteract() const;

	// 玩家选择是否正确
	UFUNCTION(BlueprintCallable, Category = "Item")
	bool IsCorrectAction(EItemAction PlayerAction) const;
	
	// 玩家是否选择了“暂时保留”
	UPROPERTY(BlueprintReadOnly, Category = "Item State")
	bool bWasKept = false;

	
	UFUNCTION(BlueprintCallable, Category = "Item")
	int GetUpgradeItemValue(){ return UpgradeItemValue; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	void ItemPickedUp(EItemAction Action);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Event")
	TSubclassOf<UUserWidget> RepeatPickHintWidget;
	
	UFUNCTION(BlueprintCallable, Category = "Item Event")
	void ShowRepeatPickHintUI();
	
	float GetStealCaughtChance();
};
