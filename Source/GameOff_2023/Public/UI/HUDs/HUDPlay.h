// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDPlay.generated.h"

class UUserWidget;
/**
 *
 */
UCLASS()
class GAMEOFF_2023_API AHUDPlay : public AHUD
{
	GENERATED_BODY()

	UFUNCTION()
	void ShowAbilityMeter();
	UFUNCTION()
	void HideAbilityMeter();

	UFUNCTION()
	void ShowPauseMenu();
	UFUNCTION()
	void HidePauseMenu();
	UFUNCTION()
	void ToggleMenu();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> AbilityMeterClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PauseMenuClass;
	// Keep a pointer to be able to hide it
	UPROPERTY()
	UUserWidget* AbilityMeter;
	// Keep a pointer to be able to hide it
	UPROPERTY()
	UUserWidget* PauseMenu;
};
