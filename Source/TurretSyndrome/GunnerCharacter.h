// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GunnerCharacter.generated.h"

UCLASS()
class TURRETSYNDROME_API AGunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float WalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float TurningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float LookUpSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float PitchMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		float PitchMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
		float InteractionDistance;

public:
	// Sets default values for this character's properties
	AGunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float value);
	void MoveStrafe(float value);
	void MoveTurn(float value);
	void MoveLookUp(float value);
	void Interact();
	FHitResult InteractionLineTrace(bool Debug);
};
