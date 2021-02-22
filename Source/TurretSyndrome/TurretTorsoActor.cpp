// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretTorsoActor.h"
#include "TurretPawn.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TurretSyndrome.h" // For LogTurret.


ATurretTorsoActor::ATurretTorsoActor()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractiveTurret = nullptr;
	
	ThisRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = ThisRootComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	NeckLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Neck Location"));
	NeckLocationComponent->SetupAttachment(RootComponent);

}

void ATurretTorsoActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretTorsoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretTorsoActor::Interact_Implementation(APawn* Interactor) {
	UE_LOG(LogTurret, Display, TEXT("Interacted with TurretTorso %s"), *GetNameSafe(this));
	if (InteractiveTurret) {
		InteractiveTurret->Interact_Implementation(Interactor);
	}
}
