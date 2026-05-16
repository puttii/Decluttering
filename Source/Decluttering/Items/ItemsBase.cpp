

#include "ItemsBase.h"


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

/*
void AItemsBase::ProcessItem(EItemAction PlayerAction)
{
	if (bProcessed)
	{
		return;
	}

	bProcessed = true;
	bWasStolen = PlayerAction == EItemAction::Steal;

	if (PlayerAction == EItemAction::Steal)
	{
		const float RandomValue = FMath::FRand();
		const bool bCaught = RandomValue <= StealCaughtChance;

		if (bCaught)
		{
			// 被发现：扣物品价值
			OnStealResult.Broadcast(this, true, -ItemValue);

			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Steal Failed! Item: %s, Lost Money: %d"),
				*ItemName.ToString(),
				ItemValue
			);
		}
		else
		{
			// 没被发现：获得物品价值
			OnStealResult.Broadcast(this, false, ItemValue);

			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Steal Success! Item: %s, Earn Money: %d"),
				*ItemName.ToString(),
				ItemValue
			);
		}

		// 偷拿不算正常判断正确
		bWasCorrect = false;
	}
	else
	{
		bWasCorrect = PlayerAction == CorrectAction;

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Item Processed: %s, Correct: %s"),
			*ItemName.ToString(),
			bWasCorrect ? TEXT("True") : TEXT("False")
		);
	}

	OnItemProcessed.Broadcast(this, PlayerAction);

	// 简单处理：处理后隐藏物品
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}
*/

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

void AItemsBase::ItemPickedUp(EItemAction Action)
{
	OnItemProcessed.Broadcast(this, Action);
}
