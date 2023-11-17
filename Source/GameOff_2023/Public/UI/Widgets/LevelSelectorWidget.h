// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelSelectorWidget.generated.h"

DECLARE_DELEGATE(FOnPreviousButtonPressedSignature)
DECLARE_DELEGATE(FOnNextButtonPressedSignature)

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API ULevelSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	FOnPreviousButtonPressedSignature OnPreviousButtonPressed;
	FOnNextButtonPressedSignature	  OnNextButtonPressed;

	UFUNCTION()
	void OnPreviousButtonClicked();
	UFUNCTION()
	void OnPlayClicked();
	UFUNCTION()
	void OnExitClicked();
	UFUNCTION()
	void OnNextButtonClicked();

	UPROPERTY(EditDefaultsOnly)
	FName LevelToExit;

	UPROPERTY(EditDefaultsOnly)
	FName LevelToGo;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LevelText;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* PreviousButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* ExitButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* PlayButton;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* NextButton;
};
