// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeMainMenu.generated.h"

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API AGameModeMainMenu : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Level load on \"Play\" clicked (do copy ref on map)")
	FName LevelToLoad;

	UFUNCTION()
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void LoadLevelSelector() const;
};
