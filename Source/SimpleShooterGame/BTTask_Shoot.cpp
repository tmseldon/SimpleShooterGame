// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* CurrentAIController = OwnerComp.GetAIOwner();
	if (CurrentAIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AShooterCharacter* AICharacter = Cast<AShooterCharacter>(CurrentAIController->GetPawn());

	if (AICharacter == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	AICharacter->AIShoot();

	// return EBTNodeResult::Type::Succeeded is the full call, but since the namespace don't have any other
	// enum that can create confusion we can call the short way as:
	return EBTNodeResult::Succeeded;
}

