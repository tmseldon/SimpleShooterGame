// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Update Player Location");
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* OwnerBlackBoard = OwnerComp.GetBlackboardComponent();

	if (PlayerPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BT Service PLayerLocation didn't get PlayerPawn reference in the constructor"));
		return;
	}

	OwnerBlackBoard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
