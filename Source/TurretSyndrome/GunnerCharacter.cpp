// Fill out your copyright notice in the Description page of Project Settings.


#include "GunnerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h" 
#include "ArenaGameMode.h"
#include "InteractiveActor.h"



// Sets default values
AGunnerCharacter::AGunnerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 1.57f)); // Average human eye height.
	CameraComponent->SetupAttachment(GetCapsuleComponent());

	WalkingSpeed = 1.0f;
	TurningSpeed = 1.0f;
	LookUpSpeed = 1.0f;
	PitchMin = -90.0f;
	PitchMax = 90.0f;

	InteractionDistance = 300.0f;
}


// Called when the game starts or when spawned
void AGunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void AGunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FHitResult Hit = InteractionLineTrace(false);
	if (Hit.Actor.IsValid()) {
		AActor* interacted = Hit.GetActor();
		IInteractiveActor* interactive = Cast<IInteractiveActor>(interacted);
		if (interactive) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(0, 0.0f, FColor::Orange, "Press F to interact");
			}
		}
	}
}


// Called to bind functionality to input
void AGunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("CharacterForward", this, &AGunnerCharacter::MoveForward);
	InputComponent->BindAxis("CharacterStrafe", this, &AGunnerCharacter::MoveStrafe);
	InputComponent->BindAxis("CharacterTurn", this, &AGunnerCharacter::MoveTurn);
	InputComponent->BindAxis("CharacterLookUp", this, &AGunnerCharacter::MoveLookUp);
	InputComponent->BindAction("CharacterInteract", IE_Pressed, this, &AGunnerCharacter::Interact);
}


void AGunnerCharacter::MoveForward(float value)
{
	if (value) {
		AddMovementInput(GetActorForwardVector(), value * WalkingSpeed);
	}
}


void AGunnerCharacter::MoveStrafe(float value)
{
	if (value) {
		AddMovementInput(GetActorRightVector(), value * WalkingSpeed);
	}
}


void AGunnerCharacter::MoveTurn(float value)
{
	if (value) {
		AddActorLocalRotation(FRotator(0.0f, value * TurningSpeed, 0.0f));
	}
}


void AGunnerCharacter::MoveLookUp(float value)
{
	if (value) {
		float new_pitch = CameraComponent->GetRelativeRotation().Pitch + value * LookUpSpeed;
		new_pitch = new_pitch < PitchMin ? PitchMin : new_pitch < PitchMax ? new_pitch : PitchMax;
		CameraComponent->SetRelativeRotation(FRotator(new_pitch, 0.0f, 0.0f));
	}
}


FHitResult AGunnerCharacter::InteractionLineTrace(bool Debug) {
	if (!GetController())
		return FHitResult();
	FVector FromLoc;
	FRotator FromRot;
	GetController()->GetPlayerViewPoint(FromLoc, FromRot);
	AArenaGameMode* gm = Cast<AArenaGameMode>(GetWorld()->GetAuthGameMode());
	FHitResult Hit = gm->VisibleLineTrace(FromLoc, FromRot, InteractionDistance, Debug);
	return Hit;
}

void AGunnerCharacter::Interact() {
	FHitResult Hit = InteractionLineTrace(true);
	if (Hit.Actor.IsValid()) {
		AActor* interacted = Hit.GetActor();
		IInteractiveActor* interactive = Cast<IInteractiveActor>(interacted);
		if (interactive) {
			interactive->Execute_Interact(interacted, this);
		}
	}
}