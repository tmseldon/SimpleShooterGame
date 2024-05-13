// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "ShooterPlayerController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnDead)
{
	Super::PawnKilled(PawnDead);

	UE_LOG(LogTemp, Warning, TEXT("Dead pawn %s"), *PawnDead->GetName());

	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(PawnDead->GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded();
	}
}
