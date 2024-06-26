// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERGAME_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Player Params")
	TSubclassOf<class UUserWidget> GameOverScreenClass;

	UPROPERTY(EditAnywhere, Category = "Player Params")
	TSubclassOf<class UUserWidget> WinnerScreenClass;

	UPROPERTY(EditAnywhere, Category = "Player Params")
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, Category = "Player Params")
	float RestartDelaySeconds = 5.f;

	FTimerHandle RestartTimer;

	UUserWidget* HUDScreenWidget;
	
};
