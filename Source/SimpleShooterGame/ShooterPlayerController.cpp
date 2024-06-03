// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	if (HUDClass != nullptr)
	{
		HUDScreenWidget = CreateWidget(this, HUDClass, TEXT("HUD Screen"));
		HUDScreenWidget->AddToViewport();
	}
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HUDScreenWidget->SetVisibility(ESlateVisibility::Hidden);
	//HUDScreenWidget->RemoveFromViewport();

	if (bIsWinner)
	{
		if (WinnerScreenClass != nullptr)
		{
			UUserWidget* WinScreenWidget = CreateWidget(this, WinnerScreenClass, TEXT("WinnerScreen"));
			WinScreenWidget->AddToViewport();
		}
	}
	else
	{
		if (GameOverScreenClass != nullptr)
		{
			UUserWidget* GameOverScreenWidget = CreateWidget(this, GameOverScreenClass, TEXT("GameOver Screen"));
			GameOverScreenWidget->AddToViewport();
		}
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelaySeconds);
}

