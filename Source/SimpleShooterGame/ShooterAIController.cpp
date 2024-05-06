// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		BlackBoardReference = GetBlackboardComponent();

		if (GetPawn() != nullptr)
		{
			BlackBoardReference->SetValueAsVector(TEXT("StartingLocation"), GetPawn()->GetActorLocation());
		}
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: there is no reference to the player pawn"));
		return;
	}

	///* Chasing the player algorithm */

	if (LineOfSightTo(PlayerPawn))
	{
		//SetFocus(PlayerPawn);
		//MoveToActor(PlayerPawn, CloseRadius);

		//Setting PlayerLocation and LastKnowPos
		BlackBoardReference->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		BlackBoardReference->SetValueAsVector(TEXT("LastKnownPos"), PlayerPawn->GetActorLocation());
	}
	else
	{
		//ClearFocus(EAIFocusPriority::Gameplay);
		//StopMovement();

		//ClearPlayerLocation
		BlackBoardReference->ClearValue(TEXT("PlayerLocation"));
	}
}
