// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HUDs/HUDPlay.h"
#include "Characters/RailCharacter.h"
#include "ActorComponents/TimeAbilityComponent.h"
#include "UI/Widgets/AbilityMeterWidget.h"
#include <GameFramework/PlayerController.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void AHUDPlay::ShowAbilityMeter()
{
	APlayerController* PC = Cast<APlayerController>(GetOwner());
	AbilityMeter = CreateWidget<UUserWidget>(PC, AbilityMeterClass);

	AbilityMeter->AddToViewport();
	if (ARailCharacter* RailCharacter = Cast<ARailCharacter>(PC->GetPawn()))
	{
		if (UAbilityMeterWidget* AM = Cast<UAbilityMeterWidget>(AbilityMeter))
		{
			UTimeAbilityComponent* TAC = RailCharacter->GetTimeAbilityComponent();
			TAC->OnMeterAmountChanged.BindUObject(AM, &UAbilityMeterWidget::OnMeterAmountChanged);
		}
	}
}

void AHUDPlay::BeginPlay()
{
	ShowAbilityMeter();
}
