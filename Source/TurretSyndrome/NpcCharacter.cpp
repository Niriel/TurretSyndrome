// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"

ANpcCharacter::ANpcCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = 200;
}

void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ANpcCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (DamageAmount > Health) {
		DamageAmount = Health;
	}

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("OUCH!"));
	}

	Health -= DamageAmount;
	if (Health <= 0) {
		Die();
	}
	return DamageAmount;
}

void ANpcCharacter::Die()
{
	Destroy();
}
