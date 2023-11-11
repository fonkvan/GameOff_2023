// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RailCharacter.h"
#include "AbilityMeterWidget.generated.h"

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API UAbilityMeterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void OnMeterAmountChanged(float MaxMeterAmount, float CurrentMeterAmount);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* AbilityBar;
};
