// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs/HUDLevelSelector.h"
#include "UI/Widgets/LevelSelectorWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/TextBlock.h"

void AHUDLevelSelector::BeginPlay()
{
	ShowLevelSelector();
}

void AHUDLevelSelector::ShowLevelSelector()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	LevelSelector = CreateWidget<UUserWidget>(PC, LevelSelectorclass);
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->OnPreviousButtonPressed.BindUObject(this, &AHUDLevelSelector::GoPreviousLevel);
		LS->OnNextButtonPressed.BindUObject(this, &AHUDLevelSelector::GoNextLevel);
	}
	LevelSelector->AddToViewport();
}

void AHUDLevelSelector::GoPreviousLevel()
{
	OnPrevious.Broadcast();
}

void AHUDLevelSelector::GoNextLevel()
{
	OnNext.Broadcast();
}

void AHUDLevelSelector::SetLevelToGo(FName LevelToGo) const
{
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->LevelText->SetText(FText::FromString(LevelToGo.ToString()));
		LS->LevelToGo = LevelToGo;
	}
}

void AHUDLevelSelector::BlockPreviousButton()
{
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->OnPreviousButtonPressed.Unbind();
	}
}

void AHUDLevelSelector::UnBlockPreviousButton()
{
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->OnPreviousButtonPressed.BindUObject(this, &AHUDLevelSelector::GoPreviousLevel);
	}
}

void AHUDLevelSelector::BlockNextButton()
{
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->OnNextButtonPressed.Unbind();
	}
}

void AHUDLevelSelector::UnBlockNextButton()
{
	if (ULevelSelectorWidget* LS = Cast<ULevelSelectorWidget>(LevelSelector))
	{
		LS->OnNextButtonPressed.BindUObject(this, &AHUDLevelSelector::GoNextLevel);
	}
}
