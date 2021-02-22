// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveProp.h"
#include "TurretSyndrome.h" // For LogTurret.

// Sets default values
AInteractiveProp::AInteractiveProp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractionCount = 0;
}

// Called when the game starts or when spawned
void AInteractiveProp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractiveProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveProp::Interact_Implementation(APawn* Interactor){
	InteractionCount++;
	UE_LOG(LogTurret, Display, TEXT("Interacted %i"), InteractionCount);
}
