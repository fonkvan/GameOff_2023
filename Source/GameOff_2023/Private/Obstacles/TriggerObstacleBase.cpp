// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/TriggerObstacleBase.h"

#include "MovieSceneSequenceID.h"
#include "Characters/RailCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATriggerObstacleBase::ATriggerObstacleBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	SetRootComponent(Mesh);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetupAttachment(RootComponent);
}

void ATriggerObstacleBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ATriggerObstacleBase::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &ATriggerObstacleBase::OnOverlapEnd);
}

void ATriggerObstacleBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ARailCharacter* PossiblePlayer = Cast<ARailCharacter>(OtherActor))
	{
		Player = PossiblePlayer;
		Trigger();
	}
}

void ATriggerObstacleBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == Player)
	{
		Player = nullptr;
	}
}


void ATriggerObstacleBase::KillPlayer()
{
	if(IsValid(Player))
	{
		Player->PlayerDeath();
	}
}

