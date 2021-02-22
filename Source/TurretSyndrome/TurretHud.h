// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TurretHud.generated.h"

/**
 *
 */
UCLASS()
class TURRETSYNDROME_API ATurretHud : public AHUD
{
	GENERATED_BODY()

public:
	ATurretHud();
	virtual void DrawHUD() override;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
