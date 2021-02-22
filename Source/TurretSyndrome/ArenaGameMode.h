// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArenaGameMode.generated.h"

/**
 *
 */
UCLASS()
class TURRETSYNDROME_API AArenaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArenaGameMode();
	virtual ~AArenaGameMode() = default;
	virtual void StartPlay();

	UFUNCTION(BlueprintPure, Category = "Stats")
		int32 GetShotsFired() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void IncShotsFired();

	UFUNCTION(BlueprintPure, Category = "Stats")
		int32 GetEnemiesKilled() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
		void IncEnemiesKilled();

	UFUNCTION(BlueprintPure, Category = "Stats")
		int32 GetLoot() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void SetLoot(int32 NewLoot);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
		void AddLoot(int32 NewLoot);

	UFUNCTION(BlueprintCallable, Category = "Default")
		FHitResult VisibleLineTrace(FVector FromLoc, FRotator FromRot, float Range, bool Debug = false);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
		AActor* SpawnTurretMissile(TSubclassOf<AActor> MissileClass, FVector Pos, FRotator Rot);
	UFUNCTION(BlueprintCallable, Category = "Weapons")
		AActor* SpawnTurretBeam(TSubclassOf<AActor> BeamClass, FVector Pos, FRotator Rot);
};
