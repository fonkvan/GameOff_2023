// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs/HUDPlay.h"
#include "Characters/RailCharacter.h"
#include "ActorComponents/TimeAbilityComponent.h"
#include "UI/Widgets/AbilityMeterWidget.h"
#include "UI/Widgets/PauseMenuWidget.h"
#include <GameFramework/PlayerController.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void AHUDPlay::ShowAbilityMeter()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	AbilityMeter = CreateWidget<UUserWidget>(PC, AbilityMeterClass);

	AbilityMeter->AddToViewport();
	if (ARailCharacter* RailCharacter = Cast<ARailCharacter>(PC->GetPawn()))
	{
		if (UAbilityMeterWidget* AM = Cast<UAbilityMeterWidget>(AbilityMeter))
		{
			UTimeAbilityComponent* TAC = RailCharacter->GetTimeAbilityComponent();
			TAC->OnMeterAmountChanged.BindUObject(AM, &UAbilityMeterWidget::OnMeterAmountChanged);
		}
	}
}

void AHUDPlay::HideAbilityMeter()
{
	if (AbilityMeter)
	{
		AbilityMeter->RemoveFromParent();
		AbilityMeter = nullptr;
	}
}

void AHUDPlay::ShowPauseMenu()
{
	// Make widget owned by our PlayerController
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	PauseMenu = CreateWidget<UUserWidget>(PC, PauseMenuClass);

	PauseMenu->AddToViewport();
	if (UPauseMenuWidget* PM = Cast<UPauseMenuWidget>(PauseMenu))
	{
		PM->OnResumed.BindUObject(this, &AHUDPlay::ToggleMenu);
	}
	PC->SetInputMode(FInputModeUIOnly());
}

void AHUDPlay::HidePauseMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (PauseMenu)
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;
	}
	ShowAbilityMeter();
	PC->SetInputMode(FInputModeGameOnly());
}

void AHUDPlay::ToggleMenu()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	if (PauseMenu)
	{
		PC->SetPause(false);
		PC->SetShowMouseCursor(false);
		HidePauseMenu();
	}
	else
	{
		ShowPauseMenu();
		PC->SetPause(true);
		PC->SetShowMouseCursor(true);
	}
}

void AHUDPlay::BeginPlay()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	PC->SetInputMode(FInputModeGameOnly());
	if (ARailCharacter* RailCharacter = Cast<ARailCharacter>(PC->GetPawn()))
	{
		RailCharacter->OnPlayerToggledPauseMenu.AddDynamic(this, &AHUDPlay::ToggleMenu);
	}
	ShowAbilityMeter();
}
