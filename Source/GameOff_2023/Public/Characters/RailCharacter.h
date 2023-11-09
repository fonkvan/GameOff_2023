// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RailCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerInteractedSignature);

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UTimeAbilityComponent;
UCLASS()
class GAMEOFF_2023_API ARailCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARailCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerInteractedSignature OnPlayerInteracted;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ChangeLanes(const FInputActionValue& Value);
	void AutoMoveForward(float DeltaTime);
	bool ValidLaneChange(int direction) const;
	void Interact();

	void SlowTime();
	void ResetTimeDilation();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	bool bChangingLanes;
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	int CurrentLane;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float LaneWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float LaneChangeSpeed;
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	FVector DesiredLocation;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement")
	float LaneChangeErrorTolerance;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Interact;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_SlowTime;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTimeAbilityComponent* TimeAbilityComponent;
};
