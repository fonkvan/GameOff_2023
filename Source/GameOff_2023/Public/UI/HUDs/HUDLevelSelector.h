// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDLevelSelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPreviousSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNextSignature);

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API AHUDLevelSelector : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnPreviousSignature OnPrevious;
	UPROPERTY(BlueprintAssignable)
	FOnNextSignature OnNext;

	UFUNCTION(BlueprintCallable)
	void SetLevelToGo(FName LevelToGo) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowLevelSelector();

	UFUNCTION()
	void GoPreviousLevel();
	UFUNCTION()
	void GoNextLevel();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LevelSelectorclass;

	UPROPERTY()
	UUserWidget* LevelSelector;
};
