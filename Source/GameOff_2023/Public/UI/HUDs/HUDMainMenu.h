// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDMainMenu.generated.h"

DECLARE_DELEGATE(FOnStartedSignature)

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API AHUDMainMenu : public AHUD
{
	GENERATED_BODY()
public:
	FOnStartedSignature OnStarted;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void ShowMainMenu();

	UFUNCTION()
	void OnStartedClicked();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY()
	UUserWidget* MainMenu;
};
