// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacles/EnemyObstacle.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RailCharacter.h"

// Sets default values
AEnemyObstacle::AEnemyObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("BlockAll");
	Mesh->OnComponentHit.AddDynamic(this, &AEnemyObstacle::OnPlayerCollide);

	InteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractArea"));
	InteractArea->SetupAttachment(Mesh);
	InteractArea->SetBoxExtent(FVector(80.0f, 300.0f, 200.0f));
	InteractArea->AddRelativeLocation(FVector(0.0f, 328.0f, 200.0f));

	InteractMark = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractMark"));
	InteractMark->SetupAttachment(Mesh);
	InteractMark->SetVisibility(false);
}

// Called when the game starts or when spawned
void AEnemyObstacle::BeginPlay()
{
	Super::BeginPlay();
	InteractArea->OnComponentBeginOverlap.AddDynamic(this, &AEnemyObstacle::OnPlayerBeginOverlap);
	InteractArea->OnComponentEndOverlap.AddDynamic(this, &AEnemyObstacle::OnPlayerEndOverlap);
}

void AEnemyObstacle::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InteractMark->SetVisibility(true);
	if (OtherActor->IsA<ARailCharacter>())
		Cast<ARailCharacter, AActor>(OtherActor)->OnPlayerInteracted.AddDynamic(this, &AEnemyObstacle::OnPlayerKilled);
}

void AEnemyObstacle::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractMark->SetVisibility(false);
	if (OtherActor->IsA<ARailCharacter>())
		Cast<ARailCharacter, AActor>(OtherActor)->OnPlayerInteracted.Remove(this, "Destroy");
}

void AEnemyObstacle::OnPlayerKilled()
{
	this->Destroy();
}

// Called every frame
void AEnemyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
