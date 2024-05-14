// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "ShooterPlayerController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnDead)
{
	Super::PawnKilled(PawnDead);

	UE_LOG(LogTemp, Warning, TEXT("Dead pawn %s"), *PawnDead->GetName());

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnDead->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
