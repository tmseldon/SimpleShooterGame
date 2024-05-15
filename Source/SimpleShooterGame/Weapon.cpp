// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot Weapon"));

	if (Root != nullptr)
	{
		/*RootComponent = Root;*/
		SetRootComponent(Root);
	}

	MeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesha Base"));
	MeshWeapon->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CheckAndSetOwnerConfig();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWeapon::CheckAndSetOwnerConfig()
{
	APawn* PlayerPawn = Cast<APawn>(GetOwner());

	if (PlayerPawn != nullptr)
	{
		PlayerOwnerController = PlayerPawn->GetController();
		if (PlayerOwnerController != nullptr)
		{
			return true;
		}
	}

	return false;
}


void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFX, MeshWeapon, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, MeshWeapon, TEXT("MuzzleFlashSocket"));

	/* 
	Debug Section
	We are getting the player viewport status to draw some debug cameras
	*/
	
		/* Drawing Viewport Camera */
		// DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90, 2, FColor::Red, true);

	/* Determine if line trace hits */
	FHitResult HitData;
	FVector ShotDirection;
	bool bHitDetected = GunTrace(HitData, ShotDirection);

	if (bHitDetected)
	{
		
		/*DrawDebugPoint(CurrentWorld, HitData.Location, 20, FColor::Red, true);*/
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactBulletFX, HitData.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitData.Location);

		/* Section to define the damage to an enemy */
		AActor* HittingActor = HitData.GetActor();

		if (HittingActor != nullptr)
		{
			FPointDamageEvent DamageEvent = FPointDamageEvent(DamageValue, HitData, ShotDirection, nullptr);
			HittingActor->TakeDamage(DamageValue, DamageEvent, PlayerOwnerController, this);
		}
	}

}

bool AWeapon::GunTrace(FHitResult& HitResultData, FVector& ShotDirection)
{
	if (PlayerOwnerController == nullptr)
	{
		bool bIsRetryConfig = CheckAndSetOwnerConfig();
		if (bIsRetryConfig == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("Problem setting the owner for this gun"));
			return false;
		}
	}

	FVector PlayerLocation;
	FRotator PlayerRotation;

	PlayerOwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	// To avoid bug where the AI can shoot itself because of the capsule collider
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	UWorld* CurrentWorld = GetWorld();
	FVector End = PlayerLocation + PlayerRotation.Vector() * MaxRange;
	ShotDirection = -PlayerRotation.Vector();

	return CurrentWorld->LineTraceSingleByChannel(HitResultData, PlayerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);
}
