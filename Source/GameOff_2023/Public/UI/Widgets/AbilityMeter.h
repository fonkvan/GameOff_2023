// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RailCharacter.h"
#include "AbilityMeter.generated.h"

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API UAbilityMeter : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	TWeakObjectPtr<ARailCharacter> OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* Canvas;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* AbilityBar;

};
