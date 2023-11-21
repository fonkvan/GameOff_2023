// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/ObstacleBase.h"
#include "BlockingObstacleBase.generated.h"

/**
 * Base class for obstacles that are (mostly) purely blocking (i.e. player dies when the player hits the obstacle)
 */
UCLASS(Abstract, NotBlueprintable)
class GAMEOFF_2023_API ABlockingObstacleBase : public AObstacleBase
{
	GENERATED_BODY()
	
};
