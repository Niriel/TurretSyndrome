// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GunnerHud.generated.h"

/**
 * 
 */
UCLASS()
class TURRETSYNDROME_API AGunnerHud : public AHUD
{
	GENERATED_BODY()
	
public:
	AGunnerHud();
	virtual void DrawHUD() override;
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
};
