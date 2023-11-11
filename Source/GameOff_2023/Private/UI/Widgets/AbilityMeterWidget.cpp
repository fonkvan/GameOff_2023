// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/AbilityMeterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"

void UAbilityMeterWidget::OnMeterAmountChanged(float MaxAmount, float CurrentAmount)
{
	AbilityBar->SetPercent(CurrentAmount / MaxAmount);
}
