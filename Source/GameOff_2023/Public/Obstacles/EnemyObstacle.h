// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleBase.h"
#include "EnemyObstacle.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS(Blueprintable)
class GAMEOFF_2023_API AEnemyObstacle : public AObstacleBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AEnemyObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	UBoxComponent* InteractArea;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	UStaticMeshComponent* InteractMark;

	UFUNCTION()
	void OnPlayerBeginOverlap(UPrimitiveComponent OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerEndOverlap(UPrimitiveComponent OnComponentEndOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
