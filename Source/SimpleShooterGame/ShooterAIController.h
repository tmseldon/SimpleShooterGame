// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERGAME_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

protected:

	virtual void BeginPlay() override;

private:
	//UPROPERTY(EditAnywhere, Category = Params, meta = (AllowPrivateAccess = "true"))
	//float CloseRadius;

	UPROPERTY(EditAnywhere, Category = Params, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* AIBehavior;

	APawn* PlayerPawn;
	UBlackboardComponent* BlackBoardReference;
	
};
