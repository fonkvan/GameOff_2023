// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Button.h"
#include "UI/Widgets/PauseMenuWidget.h"

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
}

void UPauseMenuWidget::OnResumeClicked()
{
	OnResumed.ExecuteIfBound();
}
