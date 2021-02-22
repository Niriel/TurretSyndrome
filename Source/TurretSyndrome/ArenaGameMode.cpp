// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaGameMode.h"
#include "ArenaGameState.h"
#include "DrawDebugHelpers.h" 

AArenaGameMode::AArenaGameMode() {
	GameStateClass = AArenaGameState::StaticClass();
}

void AArenaGameMode::StartPlay() {
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("StartPlayEvent called"));
	/*
	* Initialize stuff here.
	*/
	Super::StartPlay();
}

int32 AArenaGameMode::GetShotsFired() const
{
	return GetGameState<AArenaGameState>()->ShotsFired;
}

void AArenaGameMode::IncShotsFired() {
	GetGameState<AArenaGameState>()->ShotsFired++;
}

int32 AArenaGameMode::GetEnemiesKilled() const
{
	return GetGameState<AArenaGameState>()->EnemiesKilled;
}

void AArenaGameMode::IncEnemiesKilled() {
	GetGameState<AArenaGameState>()->EnemiesKilled++;
}

int32 AArenaGameMode::GetLoot() const
{
	return GetGameState<AArenaGameState>()->Loot;
}

void AArenaGameMode::SetLoot(int32 NewLoot)
{
	GetGameState<AArenaGameState>()->Loot = NewLoot;
}

void AArenaGameMode::AddLoot(int32 NewLoot)
{
	GetGameState<AArenaGameState>()->Loot += NewLoot;
}

FHitResult AArenaGameMode::VisibleLineTrace(FVector FromLoc, FRotator FromRot, float Range, bool Debug)
{
	FVector ToLoc = FromLoc + (FromRot.Vector() * Range);
	FCollisionQueryParams TraceParams;
	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, FromLoc, ToLoc, ECC_Visibility, TraceParams);
	if (Debug) {
		float Duration = 3.0f;
		if (bHit) {
			FVector HitLocation = Hit.ImpactPoint;
			DrawDebugLine(GetWorld(), FromLoc, HitLocation, FColor::Red, false, Duration);
			DrawDebugBox(GetWorld(), HitLocation, FVector(5, 5, 5), FColor::Red, false, Duration);
			DrawDebugLine(GetWorld(), HitLocation, ToLoc, FColor::Orange, false, Duration);
		}
		else {
			DrawDebugLine(GetWorld(), FromLoc, ToLoc, FColor::Green, false, Duration);
			DrawDebugBox(GetWorld(), ToLoc, FVector(5, 5, 5), FColor::Green, false, Duration);
		}
	}
	return Hit;
}

AActor* AArenaGameMode::SpawnTurretMissile(TSubclassOf<AActor> MissileClass, FVector Pos, FRotator Rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* spawned = GetWorld()->SpawnActor<AActor>(MissileClass, Pos, Rot, SpawnParams);
	if (spawned)
		IncShotsFired();
	return spawned;
}

AActor* AArenaGameMode::SpawnTurretBeam(TSubclassOf<AActor> BeamClass, FVector Pos, FRotator Rot)
{
	FActorSpawnParameters SpawnParams;
	AActor* spawned = GetWorld()->SpawnActor<AActor>(BeamClass, Pos, Rot, SpawnParams);
	if (spawned)
		IncShotsFired();
	return spawned;
}