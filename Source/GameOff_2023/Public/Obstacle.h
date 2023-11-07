// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleBase.h"
#include "Obstacle.generated.h"

/**
 *
 */
UCLASS()
class GAMEOFF_2023_API AObstacle : public AObstacleBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AObstacle();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObstacleMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
