// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameInstance.h"
#include "MVVMSubsystem.h"
#include "VM_HealthBar.h"

//void UShooterGameInstance::Init()
//{
//	Super::Init();
//
//	/*Leaving this method as WIP, instantiation for the 
//	Health VM it was done on blueprints first for testing
//	will cpome back here later*/
//}

UVM_HealthBar* UShooterGameInstance::GetGlobalHealthViewModel()
{
	 return GlobalHealthBarVM;
}
