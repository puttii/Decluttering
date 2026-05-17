

#include "ItemsBase.h"

#include "Blueprint/UserWidget.h"
#include "Decluttering/Player/MyGameMode.h"
#include "Engine/LevelScriptActor.h"
#include "Kismet/GameplayStatics.h"


AItemsBase::AItemsBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetGenerateOverlapEvents(false);
}

void AItemsBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemsBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemsBase::Interact()
{
	if (!CanInteract())
	{
		return;
	}

	// 这里先只打印，之后可以在蓝图里接 UI
	UE_LOG(LogTemp, Warning, TEXT("Clicked Item: %s"), *ItemName.ToString());
}

void AItemsBase::ProcessItem(EItemAction PlayerAction, float StealCaughtChance)
{
	if (!CanInteract())
	{
		//显示请勿重复操作UI
		ShowRepeatPickHintUI();
		return;
	}
	bWasCorrect = IsCorrectAction(PlayerAction);
	bProcessed = true;
	
	if (PlayerAction == EItemAction::Keep)
	{
		bWasKept = true;
		// 暂时保留是风险行为，不算正常整理正确
		bWasCorrect = false;
		const bool bCaught = FMath::FRand() <= StealCaughtChance;
		if (bCaught)
		{
			AMyGameMode* GameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->SetCaughtTimes(GameMode->GetCaughtTimes() + 1);
		}
		
		const int32 MoneyChanged = bCaught ? -ItemValue : ItemValue;

		OnKeepResult.Broadcast(this, bCaught, MoneyChanged);
	}
	else if (PlayerAction == EItemAction::Sort)
	{

		OnSortResult.Broadcast(this, bWasCorrect, ItemValue);

	}
	else if (PlayerAction == EItemAction::Drop)
	{
		OnDropResult.Broadcast(this, bWasCorrect, ItemValue);
	}
}

FText AItemsBase::GetItemInfoText() const
{
	FString DamageText;

	switch (DamageLevel)
	{
	case EDamageLevel::New:
		DamageText = TEXT("全新");
		break;
	case EDamageLevel::Light:
		DamageText = TEXT("轻微损坏");
		break;
	case EDamageLevel::Medium:
		DamageText = TEXT("中度损坏");
		break;
	case EDamageLevel::Heavy:
		DamageText = TEXT("重度损坏");
		break;
	default:
		DamageText = TEXT("未知");
		break;
	}

	const FString Info = FString::Printf(
		TEXT("物品：%s\n使用年限：%d 年\n损坏程度：%s\n描述：%s"),
		*ItemName.ToString(),
		UseYears,
		*DamageText,
		*ItemDescription.ToString()
	);

	return FText::FromString(Info);
}

bool AItemsBase::CanInteract() const
{
	return !bProcessed;
}

bool AItemsBase::IsCorrectAction(EItemAction PlayerAction) const
{
	if (PlayerAction == EItemAction::Keep)
	{
		return false;
	}
	return PlayerAction == CorrectAction;
}

void AItemsBase::ItemPickedUp(EItemAction Action)
{
	ProcessItem(Action, GetStealCaughtChance());
}

void AItemsBase::ShowRepeatPickHintUI()
{
	if (!RepeatPickHintWidget)	return;
	UUserWidget* Widget = CreateWidget(GetWorld(), RepeatPickHintWidget);

	if (Widget)
	{
		Widget->AddToViewport();
		// 可选：显示鼠标
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC)
		{
			PC->bShowMouseCursor = true;
		}
	}
}

float AItemsBase::GetStealCaughtChance()
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	return Cast<AMyGameMode>(GameMode)->StealCaughtChance;
}
