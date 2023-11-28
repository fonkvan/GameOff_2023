// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockingObstacleBase.h"
#include "Obstacle.generated.h"

class UStaticMeshComponent;

UCLASS(Blueprintable)
class GAMEOFF_2023_API AObstacle : public ABlockingObstacleBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	UStaticMeshComponent* Mesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};