// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SIMPLESHOOTERGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshWeapon;

	UPROPERTY(EditAnywhere, Category = FXs)
	UParticleSystem* MuzzleFX;

	UPROPERTY(EditAnywhere, Category = FXs)
	UParticleSystem* ImpactBulletFX;

	UPROPERTY(EditAnywhere, Category = FXs)
	USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = FXs)
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = Debug)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = WeaponParams)
	float DamageValue = 10;

	AController* PlayerOwnerController;

	bool CheckAndSetOwnerConfig();

	bool GunTrace(FHitResult& HitResultData, FVector& ShotDirection);
};
