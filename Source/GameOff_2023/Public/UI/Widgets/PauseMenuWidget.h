// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

DECLARE_DELEGATE(FOnResumedSignature)
/**
 *
 */
UCLASS()
class GAMEOFF_2023_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FOnResumedSignature OnResumed;

	UFUNCTION()
	void OnExitClicked();
	UFUNCTION()
	void OnResumeClicked();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Resume;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Exit;
};
