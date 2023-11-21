// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacles/ObstacleBase.h"
#include "TriggerObstacleBase.generated.h"

/**
 * Base class for obstacles that are triggered and then do something
 */
class UStaticMeshComponent;
class UBoxComponent;
UCLASS(Abstract, NotBlueprintable)
class GAMEOFF_2023_API ATriggerObstacleBase : public AObstacleBase
{
	GENERATED_BODY()

public:
	ATriggerObstacleBase();
	
protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Trigger() {};
	void KillPlayer();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Obstacle")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, Category = "Obstacle")
	UBoxComponent* TriggerVolume;

	class ARailCharacter* Player;
};
