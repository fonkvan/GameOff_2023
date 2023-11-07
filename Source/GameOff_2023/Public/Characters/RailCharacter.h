// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RailCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class USpringArmComponent;
UCLASS()
class GAMEOFF_2023_API ARailCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARailCharacter();

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

protected:
	UPROPERTY(VisibleAnywhere)
	int CurrentLane;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float LaneWidth;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;
};
