// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Weapon.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
		Input configuration section
	*/

	ShooterController = Cast<APlayerController>(Controller);

	if (ShooterController == nullptr)
	{
		return;
	}
	
	ULocalPlayer* CurrentPlayer = ShooterController->GetLocalPlayer();

	if (CurrentPlayer != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = CurrentPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			// Loading the Input Mapping for the current player
			if (InputShooterMapping != nullptr)
			{
				InputSystem->AddMappingContext(InputShooterMapping, 0);
			}
		}
	}

	/*
		Weapon configuration section
	*/

	if (WeaponClass != nullptr)
	{
		WeaponCarried = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(MoveForward, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveAhead);
		EnhancedInputComponent->BindAction(LookUp, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUpBehavior);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}

}

void AShooterCharacter::MoveAhead(const FInputActionValue& Value)
{
	// We get the 2D vector for the movement
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (ShooterController != nullptr)
	{
		const FRotator CurrentRotation = ShooterController->GetControlRotation();
		const FRotator YawRotation(0, CurrentRotation.Yaw, 0);
	
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);
	}
}

void AShooterCharacter::LookUpBehavior(const struct FInputActionValue& Value)
{
	// We get the 2D vector for the view
	FVector2D ViewVector = Value.Get<FVector2D>();

	if (ShooterController != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(ViewVector.X);
		AddControllerPitchInput(ViewVector.Y);
	}
}

