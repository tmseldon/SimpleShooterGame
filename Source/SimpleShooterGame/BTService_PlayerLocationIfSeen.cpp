// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	NodeName = TEXT("Setting/Unsetting Player Location");
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerPawn for this AI on BT Service PlayerLocationIfSeen"));
		return;
	}

	AAIController* AIController = OwnerComp.GetAIOwner();
	AShooterAIController* AIShootController = Cast<AShooterAIController>(AIController);

	if (AIShootController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No ShooterAIController for this AI on BT Service PlayerLocationIfSeen"));
		return;
	}

	UBlackboardComponent* OwnerBlackBoard = OwnerComp.GetBlackboardComponent();

	if (AIShootController->LineOfSightTo(PlayerPawn))
	{
		OwnerBlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}
	else
	{
		OwnerBlackBoard->ClearValue(GetSelectedBlackboardKey());
	}
}
