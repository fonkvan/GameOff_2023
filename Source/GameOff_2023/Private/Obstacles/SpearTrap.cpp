// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/SpearTrap.h"

#include "ActorComponents/SpearSpawningComponent.h"

ASpearTrap::ASpearTrap()
{
	SpawnerA = CreateDefaultSubobject<USpearSpawningComponent>(TEXT("Spawner A"));
	SpawnerA->SetupAttachment(RootComponent);
}


void ASpearTrap::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void ASpearTrap::Trigger()
{
	OnTriggeredEffect.Broadcast(Player, this, ProjectileClass);
}

