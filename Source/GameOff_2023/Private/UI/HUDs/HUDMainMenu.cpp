// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs/HUDMainMenu.h"
#include "UI/Widgets/MainMenuWidget.h"
#include <GameFramework/PlayerController.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void AHUDMainMenu::ShowMainMenu()
{
	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>(PC, MainMenuClass);
	if (UMainMenuWidget* MM = Cast<UMainMenuWidget>(MainMenu))
	{
		MM->OnStartClicked.BindUObject(this, &AHUDMainMenu::OnStartedClicked);
	}
	MainMenu->AddToViewport();
}

void AHUDMainMenu::OnStartedClicked()
{
	OnStarted.ExecuteIfBound();
}

void AHUDMainMenu::BeginPlay()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	PC->SetInputMode(FInputModeUIOnly());
	ShowMainMenu();
}
