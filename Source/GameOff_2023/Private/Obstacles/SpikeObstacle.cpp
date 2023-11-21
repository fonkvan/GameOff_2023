// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/SpikeObstacle.h"

ASpikeObstacle::ASpikeObstacle()
	: SpikeRaiseAmount(100.f)
{
	Mesh->SetCollisionProfileName("NoCollision");
}

void ASpikeObstacle::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void ASpikeObstacle::Trigger()
{
	FVector NewLocation = Mesh->GetComponentLocation();
	NewLocation.Z += SpikeRaiseAmount;
	Mesh->SetWorldLocation(NewLocation);
	Mesh->SetCollisionProfileName("BlockAll");
	KillPlayer();
}
