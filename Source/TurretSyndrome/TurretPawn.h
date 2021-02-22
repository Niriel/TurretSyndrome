// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveActor.h"
#include "TurretTorsoActor.h"
#include "TurretHeadActor.h"
#include "TurretPawn.generated.h"


UCLASS()
class TURRETSYNDROME_API ATurretPawn : public APawn, public IInteractiveActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Turret")
		class USceneComponent* FeetComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Turret")
		class USceneComponent* HipComponent;

	UPROPERTY(VisibleAnywhere, Category = "Turret")
		class USceneComponent* NeckComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		float PitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		float PitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		float FovMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		float FovMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		TSubclassOf<ATurretTorsoActor> TorsoActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
		TSubclassOf<ATurretHeadActor> HeadActorClass;

	UFUNCTION(BlueprintCallable, Category = "Turret")
		void DeSpawnTorso();
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void SpawnTorso();
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void DeSpawnHead();
	UFUNCTION(BlueprintCallable, Category = "Turret")
		void SpawnHead();

public:
	// Sets default values for this pawn's properties
	ATurretPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ATurretTorsoActor* TorsoActor;
	ATurretHeadActor* HeadActor;

	bool Shooting;
	APawn* Pilot;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool SetPilot(APawn* pilot, bool Force);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void Interact(APawn* Interactor);
	virtual void Interact_Implementation(APawn* Interactor) override;

private:
	void YawRot(float value);
	void PitchRot(float value);
	void Zoom(float value);
	void ExitTurret();
	void StartShooting();
	void StopShooting();
};
