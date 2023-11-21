// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameOffGameInstance.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FLevelStat
{
	GENERATED_USTRUCT_BODY()
	FLevelStat() = default;
	UPROPERTY(BlueprintReadWrite)
	FName LevelName;
	UPROPERTY(BlueprintReadWrite)
	bool bOpen;
};

UCLASS()
class GAMEOFF_2023_API UGameOffGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FLevelStat> LevelsStat;
};
