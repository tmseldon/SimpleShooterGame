// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	//if (GameOverScreenClass != nullptr)
	//{
	//	GameOverScreenWidget = CreateWidget(this, GameOverScreenClass, TEXT("GameOver Screen"));
	//}
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (GameOverScreenClass != nullptr)
	{
		GameOverScreenWidget = CreateWidget(this, GameOverScreenClass, TEXT("GameOver Screen"));
		GameOverScreenWidget->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelaySeconds);
}

