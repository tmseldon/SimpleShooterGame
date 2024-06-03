// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERGAME_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	class UVM_HealthBar* GetGlobalHealthViewModel();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthBar Reference", meta = (AllowPrivateAccess = "true"))
	class UVM_HealthBar* GlobalHealthBarVM;
	
};
