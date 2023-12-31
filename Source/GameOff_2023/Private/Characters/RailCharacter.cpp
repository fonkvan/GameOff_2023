// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/RailCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "ActorComponents/TimeAbilityComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstacles/BlockingObstacleBase.h"

// Sets default values
ARailCharacter::ARailCharacter()
	: bChangingLanes(false)
	, bIsSliding(false)
	, bIsKicking(false)
	, CurrentLane(0)
	, DefaultCapsuleSize(88.f)
	, SlideCapsuleSize(44.f)
	, MovementSpeed(600.f)
	, SlideTime(1.5f)
	, LaneWidth(200.f)
	, LaneChangeSpeed(600.f)
	, LaneChangeErrorTolerance(10)
	, RestartLevelDelay(2.f)
	, Time_SlideEnded(0.0)
	, Time_KickEnded(0.0)
	, Delay_TimeBetweenSlides(0.2)
	, Delay_TimeBetweenKicks(0.2)
	, DesiredLocation(FVector::Zero())
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetupAttachment(SpringArmComp);

	TimeAbilityComponent = CreateDefaultSubobject<UTimeAbilityComponent>(TEXT("Time Ability Component"));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(GetMesh());
}

void ARailCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ARailCharacter::OnPlayerHit);
}

// Called when the game starts or when spawned
void ARailCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
	Time_SlideEnded = GetWorld()->GetTimeSeconds();
	Time_KickEnded = GetWorld()->GetTimeSeconds();
	TArray<FEnhancedActionKeyMapping> Mappings = DefaultMappingContext->GetMappings();
	for (auto ActionKeyMapping : Mappings)
	{
		if (ActionKeyMapping.Action == Input_Interact)
		{
			InputKeyText = FText::FromString(ActionKeyMapping.Key.GetFName().ToString());
		}
	}
}

// Called every frame
void ARailCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AutoMoveForward(DeltaTime); // since we are always moving forward, it makes most sense to put in Tick

	if (bChangingLanes)
	{
		FVector NewLocation = UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), DesiredLocation, DeltaTime, LaneChangeSpeed);
		SetActorLocation(NewLocation, false);
		FVector Right = GetActorRightVector();
		float	RightDotCurrentLocation = Right.Dot(GetActorLocation());
		float	RightDotDesiredLocation = Right.Dot(DesiredLocation);
		if (FMath::IsNearlyEqual(RightDotCurrentLocation, RightDotDesiredLocation, LaneChangeErrorTolerance))
		{
			FVector Fwd = GetActorForwardVector();
			FVector FinalLocation = Fwd * Fwd.Dot(GetActorLocation()) + Right * Right.Dot(DesiredLocation);
			FinalLocation.Z = GetActorLocation().Z;
			SetActorLocation(FinalLocation, false);
			bChangingLanes = false;
			DesiredLocation = FVector::Zero();
		}
	}
}

// Called to bind functionality to input
void ARailCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	const APlayerController*			PC = Cast<APlayerController>(Controller);
	const ULocalPlayer*					LP = PC->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARailCharacter::ChangeLanes);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Started, this, &ARailCharacter::Jump);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(Input_Slide, ETriggerEvent::Triggered, this, &ARailCharacter::Slide);
		EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARailCharacter::Interact);
		EnhancedInputComponent->BindAction(Input_SlowTime, ETriggerEvent::Started, this, &ARailCharacter::SlowTime);
		EnhancedInputComponent->BindAction(Input_SlowTime, ETriggerEvent::Canceled, this, &ARailCharacter::ResetTimeDilation);
		EnhancedInputComponent->BindAction(Input_TogglePause, ETriggerEvent::Triggered, this, &ARailCharacter::TogglePauseMenu);
	}
}

// may be more difficult to change this one with splines but it is do-able
void ARailCharacter::ChangeLanes(const FInputActionValue& Value)
{
	if (bChangingLanes)
	{
		return;
	}

	FVector2D MovementVector = Value.Get<FVector2D>();

	int LaneDirection = UKismetMathLibrary::SignOfFloat(MovementVector.X);
	if (ValidLaneChange(LaneDirection))
	{
		bChangingLanes = true;
		CurrentLane += LaneDirection;
		float EstTimeToChangeLanes = LaneWidth / LaneChangeSpeed;
		float EstForwardDist = MovementSpeed * EstTimeToChangeLanes;
		DesiredLocation = GetActorLocation() + (GetActorRightVector() * LaneWidth * LaneDirection) + (GetActorForwardVector() * EstForwardDist);
	}
}

// If we use splines, it will be relatively easy to add to this function
void ARailCharacter::AutoMoveForward(float DeltaTime)
{
	const float Amt = GetMovementComponent()->GetMaxSpeed() * DeltaTime;
	AddMovementInput(GetActorForwardVector(), Amt);
}

bool ARailCharacter::ValidLaneChange(int direction) const
{
	if (!CanSlide())
	{
		return false;
	}

	int DesiredLane = CurrentLane + direction;
	return UKismetMathLibrary::Abs(DesiredLane) < 2;
}

void ARailCharacter::Interact()
{
	if (CanKick())
	{
		bIsKicking = true;
		OnPlayerInteracted.Broadcast();	
	}
}

void ARailCharacter::Jump()
{
	if (bIsSliding || bIsKicking || bChangingLanes)
	{
		return;
	}
	OnJump.Broadcast();
	Super::Jump();
}

bool ARailCharacter::CanSlide() const
{
	return !bIsSliding && !bIsKicking && !bChangingLanes && CanJump() && ((GetWorld()->GetTimeSeconds() - Time_SlideEnded) >= Delay_TimeBetweenSlides);
}

void ARailCharacter::Slide()
{
	if (CanSlide())
	{
		bIsSliding = true;
		GetCapsuleComponent()->SetCapsuleHalfHeight(SlideCapsuleSize);
		SlideAnimNotify();
		OnSlide.Broadcast();
		GetWorldTimerManager().SetTimer(TimerHandle_SlideStop, this, &ARailCharacter::SlideStop, SlideTime, false);
	}
}

void ARailCharacter::SlideStop()
{
	bIsSliding = false;
	GetCapsuleComponent()->SetCapsuleHalfHeight(DefaultCapsuleSize);
	SlideAnimNotify();
	OnSlideStop.Broadcast();
	Time_SlideEnded = GetWorld()->GetTimeSeconds();
}

bool ARailCharacter::CanKick() const
{
	return !bIsSliding && !bIsKicking && !bChangingLanes && CanJump() && ((GetWorld()->GetTimeSeconds() - Time_KickEnded) >= Delay_TimeBetweenKicks);
}

void ARailCharacter::SlowTime()
{
	UE_LOG(LogTemp, Error, TEXT("Slow triggered"));
	TimeAbilityComponent->ActivateAbility();
}

void ARailCharacter::ResetTimeDilation()
{
	TimeAbilityComponent->DeactivateAbility();
}

void ARailCharacter::OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABlockingObstacleBase::StaticClass()))
	{
		AudioComponent->Play();
		PlayerDeath();
	}
}

void ARailCharacter::PlayerDeath()
{
	DisableInput(Cast<APlayerController>(Controller));
	SetActorTickEnabled(false);
	TimeAbilityComponent->DeactivateAbility();
	SlideStop();
	GetMesh()->SetSimulatePhysics(true);
	OnDeath.Broadcast();
	GetWorldTimerManager().SetTimer(TimerHandle_RestartLevel, Cast<APlayerController>(Controller), &APlayerController::RestartLevel, RestartLevelDelay, false);
}

void ARailCharacter::TogglePauseMenu()
{
	OnPlayerToggledPauseMenu.Broadcast();
}
