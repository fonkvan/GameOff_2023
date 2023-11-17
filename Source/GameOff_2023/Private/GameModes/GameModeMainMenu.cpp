// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/GameModeMainMenu.h"
#include "UI/HUDs/HUDMainMenu.h"
#include "Kismet/GameplayStatics.h"

void AGameModeMainMenu::BeginPlay()
{
	AHUDMainMenu* hud = Cast<AHUDMainMenu>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	hud->OnStarted.BindUObject(this, &AGameModeMainMenu::LoadLevelSelector);
}

void AGameModeMainMenu::LoadLevelSelector() const
{
	UGameplayStatics::OpenLevel(this, LevelToLoad, true);
}
