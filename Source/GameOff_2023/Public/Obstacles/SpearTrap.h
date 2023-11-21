// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/TriggerObstacleBase.h"
#include "SpearTrap.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorTriggeredEffect, ARailCharacter*, Player, class ASpearTrap*, InstigatingActor, TSubclassOf<AActor>, ClassToSpawn);

/**
 * 
 */
class USpearSpawningComponent;
UCLASS(Blueprintable)
class GAMEOFF_2023_API ASpearTrap : public ATriggerObstacleBase
{
	GENERATED_BODY()

public:
	ASpearTrap();
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void Trigger() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Spawners")
	USpearSpawningComponent* SpawnerA;

public:
	UPROPERTY()
	FOnActorTriggeredEffect OnTriggeredEffect;
};
