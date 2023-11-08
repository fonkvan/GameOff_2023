// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeAbilityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF_2023_API UTimeAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateAbility();
	void DeactivateAbility();
	void UpdateMeter();

private:
	//should be a value from 0.0 - 1.0 (1.0 is normal)
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float SlowAmount;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float MaxMeterAmount;
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float CurrentMeterAmount;
	//How often the meter is updated
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float MeterUseRate;
	//How much is used per iteration
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float UseAmount;
	//How much is refilled per iteration
	UPROPERTY(EditDefaultsOnly, Category = "Ability Modifiers", meta = (AllowPrivateAccess = "true"))
	float RefillAmount;
	bool bAbilityActive;
	FTimerHandle TimerHandle_MeterUpdate;
};
