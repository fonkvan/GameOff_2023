// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/RailCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARailCharacter::ARailCharacter()
	: CurrentLane(0), LaneWidth(200.f)
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
}

// Called when the game starts or when spawned
void ARailCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARailCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AutoMoveForward(DeltaTime); //since we are always moving forward, it makes most sense to put in Tick 
}

// Called to bind functionality to input
void ARailCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	const APlayerController* PC = Cast<APlayerController>(Controller);
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARailCharacter::ChangeLanes);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(Input_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

//may be more difficult to change this one with splines but it is do-able
void ARailCharacter::ChangeLanes(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(IsValid(Controller))
	{
		int LaneDirection = UKismetMathLibrary::SignOfFloat(MovementVector.X);
		if(ValidLaneChange(LaneDirection))
		{
			CurrentLane += LaneDirection;
			FVector NewLocation = GetActorLocation() + (GetActorRightVector() * LaneWidth * LaneDirection);
			SetActorLocation(NewLocation, false);
		}
	}
}

//If we use splines, it will be relatively easy to add to this function
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
