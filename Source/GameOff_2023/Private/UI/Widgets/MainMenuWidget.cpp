// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/MainMenuWidget.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	if (Play)
	{
		Play->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayClicked);
	}
	if (Exit)
	{
		Exit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitClicked);
	}
}

void UMainMenuWidget::OnPlayClicked()
{
	OnStartClicked.ExecuteIfBound();
}

void UMainMenuWidget::OnExitClicked()
{
}
