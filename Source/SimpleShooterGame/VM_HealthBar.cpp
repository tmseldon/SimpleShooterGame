// Fill out your copyright notice in the Description page of Project Settings.


#include "VM_HealthBar.h"

float UVM_HealthBar::GetMaxHealth() const
{
	return MaxHealth;
}

void UVM_HealthBar::SetMaxHealth(float NewValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, NewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(MaxHealth);
	}
}

float UVM_HealthBar::GetCurrentHealth() const
{
	return CurrentHealth;
}

void UVM_HealthBar::SetCurrentHealth(float NewValue)
{
	if (NewValue < 0)
	{
		NewValue = 0;
	}

	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, NewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

float UVM_HealthBar::GetHealthPercent() const
{
	if (MaxHealth != 0)
	{
		return (float) CurrentHealth / (float) MaxHealth;
	}
	else
	{
		return 0;
	}
}
