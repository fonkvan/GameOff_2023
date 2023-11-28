// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/SpearProjectile.h"

#include "Characters/RailCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASpearProjectile::ASpearProjectile()
	: FlightSpeed(1000.f)
	, ActorLifetime(5.f)
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetupAttachment(MeshComponent);
	
 	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = FlightSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASpearProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovementComponent->InitialSpeed = FlightSpeed;
	GetWorldTimerManager().SetTimer(TimerHandle_Kill, this, &ASpearProjectile::DestroyProjectile, ActorLifetime);
}

void ASpearProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CapsuleComponent->OnComponentHit.AddDynamic(this, &ASpearProjectile::OnHit);
}


void ASpearProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(ARailCharacter* PossiblePlayer = Cast<ARailCharacter>(OtherActor))
	{
		PossiblePlayer->PlayerDeath();
		FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, true);
		MeshComponent->AttachToComponent(PossiblePlayer->GetMesh(), TransformRules);
	}
}

void ASpearProjectile::DestroyProjectile()
{
	Destroy();
}


