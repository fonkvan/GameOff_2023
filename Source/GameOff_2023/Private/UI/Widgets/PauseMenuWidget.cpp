// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/PauseMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
	if (Resume)
	{
		Resume->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnResumeClicked);
	}
	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnExitClicked);
	}
}

void UPauseMenuWidget::OnExitClicked()
{
	UGameplayStatics::OpenLevel(this, LevelToExit, true);
}

void UPauseMenuWidget::OnResumeClicked()
{
	OnResumed.ExecuteIfBound();
}
