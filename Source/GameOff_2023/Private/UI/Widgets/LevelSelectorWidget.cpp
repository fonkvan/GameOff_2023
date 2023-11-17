// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/LevelSelectorWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULevelSelectorWidget::NativeConstruct()
{
	if (PreviousButton)
	{
		PreviousButton->OnClicked.AddDynamic(this, &ULevelSelectorWidget::OnPreviousButtonClicked);
	}
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &ULevelSelectorWidget::OnPlayClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ULevelSelectorWidget::OnExitClicked);
	}
	if (NextButton)
	{
		NextButton->OnClicked.AddDynamic(this, &ULevelSelectorWidget::OnNextButtonClicked);
	}
}

void ULevelSelectorWidget::OnPreviousButtonClicked()
{
	OnPreviousButtonPressed.ExecuteIfBound();
}

void ULevelSelectorWidget::OnPlayClicked()
{
	UGameplayStatics::OpenLevel(this, LevelToGo, true);
}

void ULevelSelectorWidget::OnExitClicked()
{
	UGameplayStatics::OpenLevel(this, LevelToExit, true);
}

void ULevelSelectorWidget::OnNextButtonClicked()
{
	OnNextButtonPressed.ExecuteIfBound();
}
