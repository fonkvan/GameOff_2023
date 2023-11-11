// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/RailCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ActorComponents/TimeAbilityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARailCharacter::ARailCharacter()
	: bChangingLanes(false), CurrentLane(0), MovementSpeed(600.f), LaneWidth(200.f), LaneChangeSpeed(600.f), DesiredLocation(FVector::Zero()), LaneChangeErrorTolerance(10)
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
}

// Called when the game starts or when spawned
void ARailCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
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
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARailCharacter::Interact);
		EnhancedInputComponent->BindAction(Input_SlowTime, ETriggerEvent::Started, this, &ARailCharacter::SlowTime);
		EnhancedInputComponent->BindAction(Input_SlowTime, ETriggerEvent::Completed, this, &ARailCharacter::ResetTimeDilation);
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
		// SetActorLocation(NewLocation, false);
	}
}

void ARailCharacter::Interact()
{
	OnPlayerInteracted.Broadcast();
}

// If we use splines, it will be relatively easy to add to this function
void ARailCharacter::AutoMoveForward(float DeltaTime)
{
	const float Amt = GetMovementComponent()->GetMaxSpeed() * DeltaTime;
	AddMovementInput(GetActorForwardVector(), Amt);
}

bool ARailCharacter::ValidLaneChange(int direction) const
{
	int DesiredLane = CurrentLane + direction;
	return UKismetMathLibrary::Abs(DesiredLane) < 2;
}

void ARailCharacter::SlowTime()
{
	TimeAbilityComponent->ActivateAbility();
}

void ARailCharacter::ResetTimeDilation()
{
	TimeAbilityComponent->DeactivateAbility();
}

UTimeAbilityComponent* ARailCharacter::GetTimeAbilityComponent() const
{
	return TimeAbilityComponent;
}

void ARailCharacter::TogglePauseMenu()
{
	OnPlayerToggledPauseMenu.Broadcast();
}
