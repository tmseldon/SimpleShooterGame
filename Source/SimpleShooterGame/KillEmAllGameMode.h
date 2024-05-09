// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERGAME_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:

	virtual void PawnKilled(APawn* PawnDead) override;
	
};
