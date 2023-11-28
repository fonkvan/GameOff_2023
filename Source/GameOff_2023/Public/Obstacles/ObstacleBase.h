// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class GAMEOFF_2023_API AObstacleBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
