// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretHeadActor.h"
#include "TurretSyndrome.h" // For LogTurret."
#include "ArenaGameMode.h"


ATurretHeadActor::ATurretHeadActor()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractiveTurret = nullptr;

	ThisRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisRootComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	MuzzleLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocationComponent->SetupAttachment(RootComponent);

	CameraLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Location"));
	CameraLocationComponent->SetupAttachment(RootComponent);

	// Firing rate limiter.
	FiringPeriod = 0.5f;
	CanShoot = true;
	FiringPeriodHandle = FTimerHandle();
}

void ATurretHeadActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretHeadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretHeadActor::Interact_Implementation(APawn* Interactor) {
	UE_LOG(LogTurret, Display, TEXT("Interacted with TurretHead %s"), *GetNameSafe(this));
	if (InteractiveTurret) {
		InteractiveTurret->Interact_Implementation(Interactor);
	}
}

void ATurretHeadActor::SpawnProjectile() {
	if (!ProjectileClass) {
		UE_LOG(LogTurret, Error, TEXT("Turret has no projectile class"));
		return;
	}
	AArenaGameMode* gm = Cast<AArenaGameMode>(GetWorld()->GetAuthGameMode());
	gm->SpawnTurretMissile(ProjectileClass,
		MuzzleLocationComponent->GetComponentLocation(),
		MuzzleLocationComponent->GetComponentRotation()
	);
}

void ATurretHeadActor::TryToFire() {
	if (CanShoot) {
		CanShoot = false;
		GetWorldTimerManager().SetTimer(FiringPeriodHandle, this, &ATurretHeadActor::EnableFireAgain, FiringPeriod, false);
		SpawnProjectile();		
	}
}

void ATurretHeadActor::EnableFireAgain() {
	CanShoot = true;
	GetWorldTimerManager().ClearTimer(FiringPeriodHandle);
}