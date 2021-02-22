// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InteractiveActor.h"
#include "TurretTorsoActor.generated.h"

UCLASS()
class TURRETSYNDROME_API ATurretTorsoActor : public AActor, public IInteractiveActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Turret")
		class USceneComponent* ThisRootComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret")
		class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Turret")
		class USceneComponent* NeckLocationComponent;

	IInteractiveActor* InteractiveTurret; // The turret we are attached to.

public:	
	ATurretTorsoActor();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
		void Interact(APawn* Interactor);
	virtual void Interact_Implementation(APawn* Interactor) override;
};
