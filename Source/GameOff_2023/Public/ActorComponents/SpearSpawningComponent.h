// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpearSpawningComponent.generated.h"

class ASpearTrap;
class ARailCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFF_2023_API USpearSpawningComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpearSpawningComponent();

	UFUNCTION()
	void OnTriggeredEffect(ARailCharacter* Player, ASpearTrap* InstigatingActor, TSubclassOf<AActor> ClassToSpawn);
	
};
