// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "RailCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerInteractedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerToggledPauseMenuSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlideSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlideStopSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

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
	UPROPERTY(BlueprintAssignable)
	FOnPlayerToggledPauseMenuSignature OnPlayerToggledPauseMenu;
	UPROPERTY(BlueprintAssignable)
	FOnJumpSignature OnJump;
	UPROPERTY(BlueprintAssignable)
	FOnSlideSignature OnSlide;
	UPROPERTY(BlueprintAssignable)
	FOnSlideStopSignature OnSlideStop;
	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeath;

protected:
	virtual void PostInitializeComponents() override;
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

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool CanSlide() const { return !bIsSliding && !bChangingLanes && CanJump(); };
	void			 Slide();
	void			 SlideStop();
	UFUNCTION(BlueprintImplementableEvent)
	void SlideAnimNotify();

	void SlowTime();
	void ResetTimeDilation();

	UFUNCTION()
	void OnPlayerHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	void PlayerDeath();

	// UI stuff
	FORCEINLINE UTimeAbilityComponent* GetTimeAbilityComponent() const { return TimeAbilityComponent; };
	void							   TogglePauseMenu();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	bool bChangingLanes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsSliding;
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	int CurrentLane;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Capsule Settings")
	float DefaultCapsuleSize;
	UPROPERTY(EditDefaultsOnly, Category = "Capsule Settings")
	float SlideCapsuleSize;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float SlideTime;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float LaneWidth;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement", meta = (AllowPrivateAccess = "true"))
	float LaneChangeSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Rail Movement")
	float LaneChangeErrorTolerance;
	UPROPERTY(EditDefaultsOnly, Category = "Level Management")
	float RestartLevelDelay;
	UPROPERTY(VisibleAnywhere, Category = "Rail Movement")
	FVector DesiredLocation;
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Move;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Jump;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Slide;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_Interact;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_SlowTime;
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Input_TogglePause;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTimeAbilityComponent* TimeAbilityComponent;
	FTimerHandle		   TimerHandle_RestartLevel;
	FTimerHandle		   TimerHandle_SlideStop;
};
