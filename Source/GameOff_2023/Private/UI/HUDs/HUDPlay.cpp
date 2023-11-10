// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs/HUDPlay.h"
#include <GameFramework/PlayerController.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void AHUDPlay::ShowAbilityMeter()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	AbilityMeter = CreateWidget<UUserWidget>(PC, AbilityMeterClass);

	AbilityMeter->AddToViewport();
}

void AHUDPlay::BeginPlay()
{
	ShowAbilityMeter();
}
