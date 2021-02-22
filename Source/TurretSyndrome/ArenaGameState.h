// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ArenaGameState.generated.h"

/**
 *
 */
UCLASS()
class TURRETSYNDROME_API AArenaGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AArenaGameState();
	virtual ~AArenaGameState() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ShotsFired;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemiesKilled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Loot;
};
