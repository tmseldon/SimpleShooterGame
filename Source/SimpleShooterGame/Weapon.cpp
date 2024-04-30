// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
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
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFX, MeshWeapon, TEXT("MuzzleFlashSocket"));

	/* 
	Debug Section
	We are getting the player viewport status to draw some debug cameras
	*/
	
	APawn* PlayerPawn = Cast<APawn>(GetOwner());

	if (PlayerPawn == nullptr)
	{
		return;
	}

	AController* PlayerOwnerController = PlayerPawn->GetController();

	if (PlayerOwnerController == nullptr)
	{
		return;
	}
	
	FVector PlayerLocation;
	FRotator PlayerRotation;

	PlayerOwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	
	/* Drawing Viewport Camera */
	// DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90, 2, FColor::Red, true);

	/* Drawing LineTrace */
	FHitResult HitData;
	UWorld* CurrentWorld = GetWorld();
	FVector End = PlayerLocation + PlayerRotation.Vector() * MaxRange;

	bool bHitDetected = CurrentWorld->LineTraceSingleByChannel(HitData, PlayerLocation, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bHitDetected)
	{
		FVector ShotDirection = -PlayerRotation.Vector();
		/*DrawDebugPoint(CurrentWorld, HitData.Location, 20, FColor::Red, true);*/
		UGameplayStatics::SpawnEmitterAtLocation(CurrentWorld, ImpactBulletFX, HitData.Location, ShotDirection.Rotation());
	}

}
