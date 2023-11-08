// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/TimeAbilityComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTimeAbilityComponent::UTimeAbilityComponent()
	: SlowAmount(0.5f),
		MaxMeterAmount(100.f),
		CurrentMeterAmount(100.f),
		MeterUseRate(0.05f),
		UseAmount(-1.5f),
		RefillAmount(0.5f),
		bAbilityActive(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTimeAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTimeAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTimeAbilityComponent::ActivateAbility()
{
	if(bAbilityActive)
	{
		DeactivateAbility();
		return;
	}
	if(!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_MeterUpdate))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_MeterUpdate, this, &UTimeAbilityComponent::UpdateMeter, MeterUseRate, true);
	}
	UGameplayStatics::SetGlobalTimeDilation(this, SlowAmount);
	bAbilityActive = true;
}

void UTimeAbilityComponent::DeactivateAbility()
{
	UGameplayStatics::SetGlobalTimeDilation(this, 1.f);
	bAbilityActive = false;
}

void UTimeAbilityComponent::UpdateMeter()
{
	float MeterDelta = RefillAmount;
	if(bAbilityActive)
	{
		MeterDelta = UseAmount;
	}
	CurrentMeterAmount += MeterDelta;
	CurrentMeterAmount = FMath::Clamp(CurrentMeterAmount, 0.f, MaxMeterAmount);
#if UE_EDITOR
	//keep debug messages in editor only
	UE_LOG(LogTemp, Warning, TEXT("Meter amt: %f"), CurrentMeterAmount);
#endif	
	if(FMath::IsNearlyZero(CurrentMeterAmount))
	{
		DeactivateAbility();
	}
	if(FMath::IsNearlyEqual(CurrentMeterAmount, MaxMeterAmount))
	{
		CurrentMeterAmount = MaxMeterAmount;
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_MeterUpdate);
	}
}


