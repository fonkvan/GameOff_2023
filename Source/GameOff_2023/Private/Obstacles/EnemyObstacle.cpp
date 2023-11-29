// Fill out your copyright notice in the Description page of Project Settings.

#include "Obstacles/EnemyObstacle.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RailCharacter.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundCue.h"

// Sets default values
AEnemyObstacle::AEnemyObstacle()
	: bDead(false)
	, AnimMontageDelay(0.2f)
	, DestroyDelay(2.f)
	, ReturnToAnimBPDelay(0.2f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("BlockAll");

	InteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractArea"));
	InteractArea->SetupAttachment(Mesh);
	InteractArea->SetBoxExtent(FVector(80.0f, 300.0f, 200.0f));
	InteractArea->AddRelativeLocation(FVector(0.0f, 328.0f, 200.0f));

	InteractMark = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractMark"));
	InteractMark->SetupAttachment(Mesh);
	InteractMark->SetVisibility(false);

	InteractKey = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Interact Key"));
	InteractKey->SetupAttachment(InteractMark);
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
	if (ARailCharacter* RailCharacter = Cast<ARailCharacter>(OtherActor))
	{
		InteractMark->SetVisibility(true);
		InteractKey->SetVisibility(true);
		InteractKey->Text = RailCharacter->InputKeyText;
		RailCharacter->OnPlayerInteracted.AddDynamic(this, &AEnemyObstacle::OnInteract);
		GetWorldTimerManager().SetTimer(TimerHandle_AnimMontage, this, &AEnemyObstacle::PlayRandomMontage, AnimMontageDelay);
	}
}

void AEnemyObstacle::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARailCharacter* RailCharacter = Cast<ARailCharacter>(OtherActor))
	{
		InteractMark->SetVisibility(false);
		InteractKey->SetVisibility(false);
		RailCharacter->OnPlayerInteracted.RemoveDynamic(this, &AEnemyObstacle::OnInteract);
	}
}

void AEnemyObstacle::OnInteract()
{
	if (!bDead)
	{
		bDead = true;
		GetWorldTimerManager().ClearTimer(TimerHandle_AnimMontage);
		Mesh->PlayAnimation(DeathAnim, false);
		Mesh->SetCollisionProfileName("NoCollision");
		InteractMark->SetVisibility(false);
		InteractKey->SetVisibility(false);
		if (DeathSound)
		{
			DeathSound->PitchMultiplier = UGameplayStatics::GetGlobalTimeDilation(this);
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
		}
		GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &AEnemyObstacle::AfterDeath, DestroyDelay);
	}
}

void AEnemyObstacle::PlayRandomMontage()
{
	int rand = UKismetMathLibrary::RandomInteger(10);
	if (rand % 2 == 0)
	{
		Mesh->PlayAnimation(SwingA, false);
	}
	else
	{
		Mesh->PlayAnimation(SwingB, false);
	}
	if (SwingSound)
	{
		SwingSound->PitchMultiplier = UGameplayStatics::GetGlobalTimeDilation(this);
		UGameplayStatics::PlaySoundAtLocation(this, SwingSound, GetActorLocation(), GetActorRotation());
	}
	GetWorldTimerManager().SetTimer(TimerHandle_ReturnToAnimBP, this, &AEnemyObstacle::AfterMontage, ReturnToAnimBPDelay);
}

void AEnemyObstacle::AfterMontage()
{
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
}

void AEnemyObstacle::AfterDeath()
{
	Destroy();
}

// Called every frame
void AEnemyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
