// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
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
}
