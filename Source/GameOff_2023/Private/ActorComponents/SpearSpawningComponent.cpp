// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/SpearSpawningComponent.h"

#include "Characters/RailCharacter.h"
#include "Obstacles/SpearTrap.h"

// Sets default values for this component's properties
USpearSpawningComponent::USpearSpawningComponent()
{
	if(IsValid(GetOwner()))
	{
		Cast<ASpearTrap>(GetOwner())->OnTriggeredEffect.AddDynamic(this, &USpearSpawningComponent::OnTriggeredEffect);
	}
}

void USpearSpawningComponent::OnTriggeredEffect(ARailCharacter* Player, ASpearTrap* InstigatingActor, TSubclassOf<AActor> ClassToSpawn)
{
	if(IsValid(InstigatingActor) && IsValid(ClassToSpawn) && (GetOwner() == InstigatingActor))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//This only works by setting pitch of the spawner to 90
		FTransform SpawnTM = FTransform(GetComponentRotation(), GetComponentLocation());
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}
