// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "VM_HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERGAME_API UVM_HealthBar : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;

	/* Setter and Getter for the health bindable property*/
	void SetCurrentHealth(float NewValue);
	float GetCurrentHealth() const;

	/* Setter and Getter for the MAX health bindable property*/
	void SetMaxHealth(float NewValue);
	float GetMaxHealth() const;


protected:

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float CurrentHealth;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	float MaxHealth;



	
};
