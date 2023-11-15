// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

DECLARE_DELEGATE(FOnStartClickedSignature)

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API UMainMenuWidget : public UUserWidget
{

	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

public:
	FOnStartClickedSignature OnStartClicked;
	UFUNCTION()
	void OnPlayClicked();
	UFUNCTION()
	void OnExitClicked();

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Play;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Exit;
};
