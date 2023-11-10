// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widgets/AbilityMeter.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanel.h"

void UAbilityMeter::NativeConstruct()
{
	Super::NativeConstruct();

	if (AbilityBar && Canvas)
	{
		Canvas->AddChildToCanvas(AbilityBar);
	}
