// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockingObstacleBase.h"
#include "EnemyObstacle.generated.h"

class UAnimMontage;
class UAnimSequence;
class USkeletalMeshComponent;
class USoundCue;
class UStaticMeshComponent;
class UBoxComponent;
class UTextRenderComponent;

UCLASS(Blueprintable)
class GAMEOFF_2023_API AEnemyObstacle : public ABlockingObstacleBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AEnemyObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnInteract();

	void PlayRandomMontage();
	void AfterMontage();
	void AfterDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	bool bDead;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	float AnimMontageDelay;
	UPROPERTY(EditDefaultsOnly)
	float DestroyDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	float ReturnToAnimBPDelay;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	UBoxComponent* InteractArea;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
	UStaticMeshComponent* InteractMark;
	UPROPERTY(EditDefaultsOnly, Category = "Obstacle")
	UTextRenderComponent* InteractKey;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* SwingA;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* SwingB;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimSequence* DeathAnim;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* SwingSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue*	 DeathSound;
	FTimerHandle TimerHandle_AnimMontage;
	FTimerHandle TimerHandle_Destroy;
	FTimerHandle TimerHandle_ReturnToAnimBP;
};
