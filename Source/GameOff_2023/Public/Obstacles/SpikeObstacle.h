// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/TriggerObstacleBase.h"
#include "SpikeObstacle.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEOFF_2023_API ASpikeObstacle : public ATriggerObstacleBase
{
	GENERATED_BODY()

public:
	ASpikeObstacle();
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void Trigger() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Obstacle")
	float SpikeRaiseAmount;
};
